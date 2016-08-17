#include "process.h"

//  Process Constructor
//  Initalizes a process as a single burst of CPU usage,
//  which may or may not be allowed to run all at once.
//  When that CPU time is complete, so is the process.

Process::Process( int id )  // a constructor
{
    myId = id;
    bursts = 1;         // one big CPU requirement now
    usages[0] = 80 + rand() % 120;
    nextState[0] = 'Q'; // all done!
}

//  Run a Process for some time
//  The process would like to complete its current CPU burst,
//  but is currently only allowed what is granted to it.
//  Parameters:
//  	clock		(modified int)	time on simulation clock
//  	allowance	(input int)	time allowed to run with
//	next		(output char)	the process next state after this
//		'Q' = process is complete;  'X' = process wishes to run more
//  Post-Condition:
//  	the clock will have advanced until either the allowed time
//  	has been used up, or the current CPU burst is complete
//  	(whichever happens earlier).  There will be no idle CPU time.
//  Also:  The history log for this Process will record what is known
//  	at this time
void Process::run( int &clock, int allowance, char &next )
{
    //cout << "PID: " << myId << " Usage: " << usages[0] << endl;
	remainingTime = usages[currentCycle];
    addLog(clock, next);
	int start = 0;
    for(start = clock; clock-start < allowance && remainingTime > 0; clock++) {
        remainingTime= remainingTime - 1;
    }
    if (remainingTime == 0) {
        next = 'Q';
        addLog(clock, 'Q');
    }
    else {
        addLog(clock, '-');
    }
	if (currentCycle != 9)
		currentCycle = currentCycle + 1;
	else
		currentCycle = 1;
	usages[currentCycle] = remainingTime;
    //cout << "Clock: " << clock << " Time Left: " << usages[0] << endl;
}

