#include <iostream>
#include "process.h"

using namespace std;

// History Displayer
// Produces an Ascii-graphic representation of the history of a process
// within a simulation of job scheduling.  The history is recorded as a
// series of time stamps, represented here as integer time values and
// characters representing state.
// Paramaters:
//     history  input ProcList array	linked lists of events and times
//     size	input int		number of elements in array
//     start	input int		beginning of time frame of interest
//     stop	input int		end of time frame of interest
// Pre-Conditions:
//     'history' concludes with an entry with state 'Q' for completion
//     'start' and 'stop' are both positive integers, with start < stop
//     NOTE:   'start' or 'stop' may be outside the range in the history
// Results:
//     A display of between 20 and 50 printable characters representing
//     the job history within the time range of interest, using the
//     characters stored within the given list.  Events outside the actual range
//     of the job history will be displayed with blanks.
void displayHistory(Process history[], int size, int start, int stop )
{
	const int numChar = 50;
    char processHistory[numChar + 1];
    cout << "Time : "<<start << " " << stop << endl;
    for (int i = 0; i < size; i++) {
        cout << i << '\t';
		//ProcList temp = history[i].getLog();
        ProcIterator iter = history[i].getLog().begin();
        for(int i = 0; i <= numChar; i++){
         processHistory[i] = '\0';
         }
         int j = 0;
         double totalTime = stop - start, currFrac = 0;
         char currState = ' ', finalChar = ' ';
         while (iter.time() < start) {
             currState = iter.state();
             iter.advance();
         }
         int time = start;
         while (time < stop && currState != 'Q') {
         currFrac = (((iter.time() < stop) ? iter.time() : stop) - time) / totalTime;
         int numChars = currFrac * numChar;
         if (currState == 'X' && numChars == 0) {
             numChars = 1;
         }
         for (int k = 0; k < numChars; k++) {
             processHistory[j] = currState;
             j = j + 1;
         }
         time = iter.time();
         if (time >= stop) {
             finalChar = currState;
         }
         currState = iter.state();
             iter.advance();
         }
         while(j < numChar) {
         processHistory[j] = finalChar;
         j = j + 1;
         }
         cout << "\"" << processHistory << "\"" << endl;
        
    }
}