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
    master.restart();
    
    for (int i=0; i < size; i++) {
        future.insert( i, arrival[i], 'X');	// all want to run
        tasks[i]->restart();			// and start at beginning
        tasks[i]->addLog( arrival[i], '-');	// might have to wait
    }
    
    for (int i = 1; i < 20; i++) {
        tasks[i] = NULL;
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
                addProcess(pid); //add back into future
            }
            else if (next == &master) {
                //future.insert(pid, clock + 1000, 'X');
                pid = master.createProcess(tasks, future, clock);
                future.insert(pid, console.getReadyTime(), 'X'); //insert new process after it's made
                tasks[pid]->addLog(console.getReadyTime(), '-'); //start its log
            }
            else if ( next != NULL) { //wants device
                next->request(pid, clock, tasks, future);
            }
        }
    }
}

// min heap insert
//  Adapted from Prof. Christman's lecture notes
//  Inserts a process into the min heap based on a process's remainingTime
//  Parameters:
//  	pid	(input int)		pid of process to insert
//  Pre-condition:
//      heap is not full, there are less than 20 processes overall
void SRT::insert(int pid)
{
    int pos = nextEmpty; //insert into next empty space
    while ( (pos > 1) && heap[pos/2]->getRemainingTime() > procs[pid]->getRemainingTime() )
    {
        heap[pos] = heap[pos/2];	// move parent down if it has more remaining time
        pos = pos/2;		// continue towards root
    }
    heap[pos] = procs[pid];		// insert new data
    nextEmpty++;
}

//  heap removal
//  Adapted from Prof. Christman's lecture notes
// Remove the process with the shortest reamining time and shift other processes
//  Parameters:
//  	none
//  Pre-condition:
//      heap is not empty
//  Post-condition:
//      return value is pid of process to run
int SRT::pop()
{
    int pid = heap[1]->getID();	// return the shortest time process
    bool done = false;          // not done fixing the heap
    int pos = 1;
    nextEmpty--;		// rightmost leaf now empty
    heap[pos] = heap[ nextEmpty ];
    int child = 2;			// the left child of the root
    while (child < nextEmpty && !done )		// stop at bottom or when in order
    {
        if (child+1 < nextEmpty		// pick smaller child if it exists
            && heap[child]->getRemainingTime() > heap[child+1]->getRemainingTime())
            child = child+1;
        if ( heap[child]->getRemainingTime() > heap[pos]->getRemainingTime() ) //if parent has less time
            done = true;			//    heap is in order
        else
        {
            Process *temp = heap[child]; //swap parent and child
            heap[child] = heap[pos];
            heap[pos] = temp;
            pos = child;			// continue down the tree
            child = 2*pos;			// starting with the new left child
        }
    }
    return pid;
}
