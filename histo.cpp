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
#include <iostream>
#include <iomanip>
#include "process.h"
using namespace std;

//adapted from the Prof. Christman's histo.cpp from HW2

void displayHistory(Process history[], int size, int start, int stop) {
	char display[50];			// to hold the output
	int outpos;				// next output position to fill
	int scan;				// next input data item to scan

	char  currentState;			// current process state in history
	int time;				// current time examined
	int range = stop - start;		// total time period
	int increment = 1 + range / 40;	// round fractions upwards

	cout << "Time:  " << start << setw(range / increment) << stop << endl;

	for (int j = 0; j < size; j++) {
		for (int i = 0; i < 50; i++)		// intialize display
			display[i] = ' ';

		ProcList &localHistory = history[j].getLog();	// reference to process log
		localHistory.condense();
		cout << localHistory;
		ProcIterator iter = localHistory.begin();	// starting at its first point

		if (start < iter.time())		//histo starts before log
			outpos = (iter.time() - start) / increment;	// move to relevant index
		else
			outpos = 0;				// start at beginning of display
		time = start + outpos * increment;	// identify smulation time

		currentState = iter.state();	// initialize if loop never repeats
		while (time <= stop && time >= iter.time()) { //get current state at current time
			currentState = iter.state();
			iter.advance();
		}

		// collect relevant data into the output array   
		while (time <= stop && currentState != 'Q' && iter != localHistory.end()) {
			//record currentState until next state
			while (time <= stop && time < iter.time()) {
				display[outpos] = currentState;
				outpos++;
				time += increment;
			}
			currentState = iter.state();	// update currentState
			iter.advance();			// and find when it ends

			//look for skipped X states
			while (currentState != 'Q' && time >= iter.time()) {
				if (currentState == 'X')	// missed CPU data
					display[outpos - 1] = 'X';
				currentState = iter.state();	// update state
				iter.advance();			//and find when it ends
			}

		}
		display[outpos] = '\0';
		cout << setw(5) << j + 1 << setw(2) << " " << display << endl;
	}
}
