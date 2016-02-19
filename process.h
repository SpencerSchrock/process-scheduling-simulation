#include "proclist.h"
#include <stdlib.h>

// A description of a process, executed in the process scheduling simulation
class Process
{
    private:
	int myId;		// an identifier for the larger picture

	// A description of the process's total CPU needs
	int bursts;		// total number of CPU bursts (<= 10)
	int usages[10];		// lengths of each burst
	char nextState[10];	// what to do after each burst

	// A desription of what this process is doing now
	int currentCycle;	// which burst is next ro run or continue
	int remainingTime;	// how much time left on current burst

	// A desription of what this process has done so far
	ProcList log;

    public:
        Process( int id );	// the constructor appears in the .cpp

	void restart()		// start at the very beginning
	{
	    currentCycle = 0;
	    remainingTime = usages[0];
	    log.clear();	// empty the log
	}

	void addLog( int time, char state )	// record an event
	{
	    log.pushBack( myId, time, state );
	}

	ProcList &getLog()
	{
	    return log;		// get summarized results at end
	}

	//  run for a little while (in .cpp file)
	void run( int &clock, int allowance, char &next );
};
