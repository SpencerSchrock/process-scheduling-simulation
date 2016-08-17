#include <iostream>
using namespace std;

#include "histo.h"

// Process Scheduler
// This represents the part of an operating system that manages processes,
// choosing which to assign the CPU (assuming a single-processor system).
// It will maintain a collection of processes that are currently ready
// to use the CPU, and then choose which to run next.
//
// The time on the system clock is not required for this object,
// so all of the time fields in the linked list objects are set to zero.

class Scheduler
{
    private:
	ProcList readySet;	// set of processes ready to run
	ProcList future;	// list of future events
	int clock;		// current clock time for simulation
    public:
	void addProcess( int procId )
	{
	    readySet.pushBack( procId, 0, 'X');
	}
	void chooseProcess( int &procId )
	{
	    char hold;
	    readySet.popFront( procId, hold );
	}
	bool noneReady()
	{
	    return readySet.empty();
	}
    void runScheduler( Process[], int[], int, int );
};
