// History Displayer
// Produces an Ascii-graphic representation of the history of a process
// within a simulation of job scheduling.  The history is recorded as a
// series of time stamps, represented here as integer time values and
// characters representing state.
// Paramaters:
//     history  input		array of Process pointers
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
#include <math.h>
using namespace std;

void displayHistory(Process *history[], int size, int start, int stop )
{
    const int histLength = 50; //number of printable characters representing job history
    char display[histLength + 1]; //the character array that holds job history
    
    cout << "Time: " << start << setw( histLength + 1) << stop << endl;
    
    for (int i = 0; i < size; i++) { //repeat for every process
        ProcList &localHistory = history[i]->getLog(); //reference to process log
        localHistory.condense();
        ProcIterator iter = localHistory.begin(); //iterator to traverse the log
        
        for( int i = 0; i <= histLength; i++ ) { //wipe the character array
            display[i] = '\0';
        }
        
        cout << setw(5) << i + 1 << setw(1) << " ";  //use loop variable to print current pid
        int j = 0; //index for the display[] array
        
        double totalTime = stop - start; //range of the time interval being printed
        double currFrac = 0; //fractional amount of the display[] array a state will occupy

        //currState holds the current state from localHistory at the current time
        //finalChar holds the last state to account for rounding errors from earlier states
        //finalChar also accounts for when the end time is after the largest time stamp because it is initialized as a space character
        char currState = ' ', finalChar = ' ';
        
        while (iter.time() < start) { // before we get to the start time, find out the current state
            currState = iter.state();
            iter.advance();
        }
        
        int time = start; //time holds the value of the last read time
        
        //process data while we haven't reached our stop time or the end of our data
        while ( time < stop && currState != 'Q' && iter != localHistory.end() ) {
            //calculate the fraction of the current state based on the times and totalTime
            currFrac = (((iter.time() < stop) ? iter.time() : stop) - time) / totalTime;

            //numChars determines how many chars in the display[] array the current state will occupy
            int numChars = round(currFrac * histLength);
            
            if ((currState == 'X' && numChars == 0)) { //ensures CPU states are not ignored
                numChars = 1;
            }
            
            //j < histLength included in case everything rounded up and we're out of space
            for (int k = 0; k < numChars && j < histLength; k++) { //fill display[] for current state
                display[j] = currState;
                j = j + 1;
            }
            time = iter.time(); //advance time
            //if the next time is out of range store the finalChar for rounding errors
            //if the log reaches its Q before the stop time, finalChar retains its space value to fill the display[] array with space chracters
            if (time >= stop) {
                finalChar = currState;
            }
            currState = iter.state(); //advance state
            iter.advance(); //move to next node in logHistory
        }
        //finishes the display[] array after processing given data. accounts for rounding errors or when the ending time is after the largest time stamp
        while(j < histLength) {
            display[j] = finalChar;
            j = j + 1;
        }
        cout << "|" << display << "|" << endl;
    }
}
