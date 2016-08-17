#include "scheduler.h"

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
void Scheduler::runScheduler( Process tasks[], int arrival[], int size, int allowance )
{
    int pid;			// process wanting action
    char nextAct;		// and the action it wants

    for (int i=0; i < size; i++)
    {
	future.insert( i, arrival[i], 'X');	// all want to run
	tasks[i].restart();			// and start at beginning
	tasks[i].addLog( arrival[i], '-');	// might have to wait
    }
    
    clock = 0;			// initialize simulation clock
    //  repeat while anything is ready to run now or later
    while (!noneReady() || !future.empty() )
    {
        //load new processes ready to be run
		//cout << "running while loop" << endl;
		//cout << "Clock: " << clock << endl;
		//cout << "future: " << future;
        while (!future.empty() && future.leadTime() <= clock) {
            future.popFront(pid, nextAct); //remove from future
            addProcess(pid); //adds to ready set
        }
        //pick a process to run
        chooseProcess(pid);
        tasks[pid].run(clock, allowance, nextAct);
        //cout << tasks[pid].getLog() << endl;
        if (nextAct != 'Q') { 
            addProcess(pid);
        }
        else {
            nextAct = 'X';
        }
        
    }
    //for (int i=0; i < size; i++)
    //{
    //    cout << tasks[i].getLog();	// might have to wait
    //}
}
