// Device Driver Simulation
// A simplified version of the behavior of a device driver.
// It is notified of when a request arrives, and then it
// determines when that action begins and ends.

#include "proclist.h"

class Process;
class Device
{
    private:
	ProcList requests;
	char action;		// letter used for display
	int duration;		// how long the operation might take
	int readyTime;		// when next operation may start
    public:
    Device() {}
	Device( char a, int d ) : action(a), duration(d), readyTime(0) { }
	void restart()
	{
	    readyTime = 0;
	}
    int getReadyTime()
    {
        return readyTime;
    }
    void request( int, int, Process* [], ProcList & );
};
class Console : public Device
{
private:
    int numProcesses;       //number of processes running
public:
    Console() : numProcesses(1){ }
    int createProcess(Process *tasks[], ProcList &future, int clock);   //launches a process
    int getNumProcesses()
    {
        return numProcesses;
    }
    void restart()
    {
        numProcesses = 1;
    }
};

extern Device disk, net, console, cpu;
extern Console master;
