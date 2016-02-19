#include "process.h"

//  Process Constructor
//  Initalizes a process as a single burst of CPU usage,
//  which may or may not be allowed to run all at once.
//  When that CPU time is complete, so is the process.

Process::Process( int id )  // a constructor
{
    myId = id;
    bursts = 4 + rand() % 3;    // several CPU bursts
    //cout<<"id: "<<id<<endl;
    for (int i=0; i < bursts; i++)
    {
        usages[i] = 80 + rand() % 120;
        //cout << "usages["<<i<<"] = " << usages[i]<<endl;
        nextState[i] = 'D';     // some disk activity
    }
    nextState[bursts-1] = 'Q';  // all done!
}

//  Run a Process for some time
//  The process would like to complete its current CPU burst,
//  but is currently only allowed what is granted to it.
//  Parameters:
//  	clock		(modified int)	time on simulation clock
//  	allowance	(input int)	time allowed to run with
//	next		(output char)	the process next state after this
//		'Q' = complete;  'X' = wishes more CPU;  'D' == wishes disk
//  Post-Condition:
//  	the clock will have advanced until either the allowed time
//  	has been used up, or the current CPU burst is complete
//  	(whichever happens earlier).  There will be no idle CPU time.
//  Also:  The history log for this Process will record what is known
//  	at this time
void Process::run( int &clock, int allowance, char &next )
{
    addLog(clock, 'X'); //add the 'x' to the log
    int start; //start is used here to record the initial clock time
    for(start = clock; clock-start < allowance && remainingTime > 0; clock++) { //run while allowed or needed
        remainingTime = remainingTime - 1;
    }
    if (remainingTime == 0) { // if current burst done
        next = nextState[currentCycle];
        if (next == 'Q') { //if done, mark in log
            addLog(clock, next);
        }
        currentCycle = currentCycle + 1; //advance cycle
        remainingTime = usages[currentCycle]; //update time for next CPU burst
    }
    else { //will be waiting to finish CPU burst
        next = 'X';
        addLog(clock, '-');
    }
}

