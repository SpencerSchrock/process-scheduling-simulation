// A quick driver to test the History Display routine
// It just fabricates a single job history to see what it does
//
#include <iostream>
using namespace std;

#include "scheduler.h"
#include "device.h"

/*
 driver.cpp:
 allocates an array for 'many' processes
 
 for each simulation (each scheduling policy)
 
 initialize Process array to one user-interactive shell
 (a derived class of process that interacts with the user)
 all other array elements should be NULL pointers
 
 call runScheduler, with only one process, ready at time 0
 
 count the non-NULL pointers in the Process array
 
 call displayHistory so it will display all process histories
 */
int main()
{
   Scheduler *scheds[] = 	    // make some process schedulers
	{ new FCFS(), new RoundRobin(), new Priority(), new Preempt(), new SRT() };
    Process *tasks[20] = {new Interact(0)};		    // 4 processes
    for (int i = 1; i < 20; i++)
    {
        tasks[i] = NULL;
    }

   int arrival[] = {0};   // arrive at these times
 
   for (int i=0; i<5; i++)
   {
	scheds[i]->runScheduler( tasks, arrival, 1 );
    cout << scheds[i]->getName() << endl;
	displayHistory( tasks, master.getNumProcesses(), 0, 20000 );
   }
}

