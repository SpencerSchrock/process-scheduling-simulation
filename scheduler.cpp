#include "scheduler.h"

const int DISKTIME = 200;		// how long a disk action requires

//  Request to access the disk (secondary storage)
//  A process may occasionally need to access a file or the
//  virtual memory system.  The disk may only service one
//  process at a time, and its readiness will be simulated
//  with a time index also.
//  Parameters:
//  	pid  	  (input int)		process id (subscript to tasks[])
//  	clock	  (input int)		overall simulation clock time
//  	diskReady (modified int)	when the disk is available for use
//	tasks	  (Process array)	given to update process history
//	future	  (modified ProcList)	a process may proceed after using disk
//

void diskRequest( int pid, int clock, int &diskReady, Process tasks[], ProcList &future )
{
    
    
    if (clock >= diskReady){ //disk is free
        diskReady = clock + DISKTIME;
        tasks[pid].addLog(clock, 'D');
    }
    else {
        tasks[pid].addLog(clock, '-');
        tasks[pid].addLog(diskReady, 'D');
        diskReady = diskReady + 200;
    }
    tasks[pid].addLog(diskReady, '-');
    future.insert(pid, diskReady, 'X');
}


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
    int diskReady = 0; //initialize diskReady
    //  repeat while anything is ready to run now or later
    while (!noneReady() || !future.empty() )
    {
        //load new processes ready to be run
        while (!future.empty() && future.leadTime() <= clock) {
            future.popFront(pid, nextAct); //remove from future
            addProcess(pid); //adds to ready set
        }
        if (noneReady()) //if processes want to run in future and none ready now, advance clock
            clock = future.leadTime();
        else {
        //pick a process to run
        chooseProcess(pid); //pid will be -1 if none are ready
        if (pid != -1) { //if readyset isn't empty
            tasks[pid].run(clock, allowance, nextAct);

            if (nextAct == 'X') { //process still wants to run
                future.insert(pid, clock, 'X'); //add back into future
            }
            else if (nextAct == 'D') {
                diskRequest(pid, clock, diskReady, tasks, future);
            }
            }
        }
    }
}
