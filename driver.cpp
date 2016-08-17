// A quick driver to test the History Display routine
// It just fabricates a single job history to see what it does
//
#include <iostream>
using namespace std;

#include "scheduler.h"
#include "device.h"

int main()
{
   Scheduler *scheds[] = 	    // make some process schedulers
	{ new FCFS(), new RoundRobin(), new Priority(), new Preempt(), new SRT() };
   Process *tasks[] = 		    // 4 processes
    { new Computation(0), new Download(1), new Interact(2), new Download(3) };
    //{ new Computation(0), new Computation(1), new Computation(2), new C(3), new Interact(4)};
	//{ new Computation(0), new Computation(1), new Download(2),new Download(3), new Interact(4) };
   int arrival[] = {0, 40, 80, 120, 160};   // arrive at these times
 
   for (int i=0; i<5; i++)
   {
	scheds[i]->runScheduler( tasks, arrival, 4 );
    cout << scheds[i]->getName() << endl;
	displayHistory( tasks, 4, 0, 4000 );
   }
}

