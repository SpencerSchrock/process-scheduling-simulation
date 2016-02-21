// A quick driver to test the History Display routine
// It just fabricates a single job history to see what it does
//

#include <iostream>
using namespace std;

#include "scheduler.h"

int main()
{
   Scheduler sched;		    // make a process scheduler
   Process tasks[] = 		    // 3 processes
	{ Process(0), Process(1), Process(2) };	
   int arrival[] = {0, 40, 80};   // arrive at these times
 
   cout << "First Come First Served" << endl;
   sched.runScheduler( tasks, arrival, 3, 500000 );	// FIFO
   displayHistory( tasks, 3, 0, 3000 );
   cout << endl << "Quanta of 70" << endl;
   sched.runScheduler( tasks, arrival, 3, 70 );	// RR generous
   displayHistory( tasks, 3, 0, 3000 );

}

