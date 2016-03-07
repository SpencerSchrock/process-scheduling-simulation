#include "scheduler.h"
#include "device.h"

//  Scheduler Simulation
//  Simulates a process scheduler for a collecdtion of tasks
//  Parameters:
//  	tasks		(modified process array)description of tasks to run
//  	arrival		(input int array)	arrival in simulation time
//  	size		(input int)		number of elements in arrays
//  	allowance	(input int)		maximal CPU allowance 
//		(a large 'allowance' simulates First Come First Served)
//  Each Process includes a history of its activity which is
//  pupulated during the simulation and displayed afterwards.
//  
//  The scheduler includes a readySet of processes that are currently
//  wishing to use the CPU, and a future list of events that will
//  occur later in the simulation.  A simulation clock advances to
//  identify which events occur in which order.
void Scheduler::runScheduler( Process *tasks[], int arrival[], int size)
{
    int pid;			// process wanting action
    Device *next;		// and the device it wants
    clock = 0;			// initialize simulation clock
    
    cpu.restart(); //initialize devices for each simulation
    disk.restart();
    net.restart();
    console.restart();
    
    for (int i=0; i < size; i++) {
        future.insert( i, arrival[i], 'X');	// all want to run
        tasks[i]->restart();			// and start at beginning
        tasks[i]->addLog( arrival[i], '-');	// might have to wait
    }

    //  repeat while anything is ready to run now or later
    while ( !noneReady() || !future.empty() ) {
        //load new processes ready to be run
        while ( !future.empty() && future.leadTime() <= clock ) {
            char hold;
            future.popFront(pid, hold); //remove from future
            addProcess(pid); //adds to ready set
        }
        if ( noneReady() ) //if processes want to run in future and none ready now, advance clock
            clock = future.leadTime();
        else {
            chooseProcess(pid);
            tasks[pid]->run(clock, allowance(), next);
            if ( next == &cpu ) { //process still wants to run
                future.insert(pid, clock, 'X'); //add back into future
            }
            else if ( next != NULL) { //wants device
                next->request(pid, clock, tasks, future);
            }
        }
    }
}
