#include <iostream>
using namespace std;

// History Displayer
// Produces an Ascii-graphic representation of the history of a process
// within a simulation of job scheduling.  The history is recorded as a
// series of time stamps, represented here as integer time values and
// characters representing state.
// Paramaters:
//     state	input char array	what state this job changed to
//     times	input int array		when this job changed state
//     start	input int		beginning of time frame of interest
//     stop     input int		end of time frame of interest
// Pre-Conditions:
//     'state' consists of printable characters, with 'Q' marking end of job
//     'times' consists of increasing positive integers
//     the number of meaningful values in both arrays is equal (including 'Q')
//     'start' and 'stop' are both positive integers, with start < stop
//          and ( stop-start >= 20 )
//     NOTE:  'start' or 'stop' may have values outside the range in 'when'
// Results:
//     A display of between 20 and 50 printable characters representing
//     the job history within the time range of interest, using the
//     characters stored within 'state'.  Events outside the actual range
//     of the job history will be displayed with blanks.

void displayHistory( const char state[], const int times[], int start, int stop )
{
	const int numChar = 50; //number of printable characters representing job history
    char history[numChar + 1]; //the character array that holds job history terminated by an extra null character
    for(int i = 0; i <= numChar; i++){
        history[i] = '\0';
    }
	//i is the index for the state[] and times[] arrays. 
	//j is the index for the history[] array
    int i = 0, j = 0;
	//totalTime represents the range of the time interval being printed
	//currFrac represents the fractional amount of the history[] array a state will occupy
    double totalTime = stop - start, currFrac = 0; 
	//currState holds the current state from the state[] array based upon the time from the times[] array
	//finalChar will hold the last state to account for rounding errors from earlier states
	//finalChar also accounts for when the end time is after the largest time stamp because it is initialized as a space character
	char currState = ' ', finalChar = ' '; 
    while (times[i] < start) { // before we get to the start time, find out the current state
        currState = state[i];
        i = i+1;
    }
    int time = start; //time holds the value of the current time from the times[] array
    while (time < stop && currState != 'Q') { //process data while we haven't reached our stop time or the end of state[] array
		currFrac = (((times[i] < stop) ? times[i] : stop) - time) / totalTime; //calculate the fraction of the current state based on the times and totalTime.
		//numChars determines how many chars in the history[] array the current state will occupy
		int numChars = currFrac * numChar; 
        if (currState == 'X' && numChars == 0) { //ensures CPU states are not ignored due to short run time
            numChars = 1;
        }
        for (int k = 0; k < numChars; k++) { //fill the history[] array with the relavant state
            history[j] = currState;
            j = j + 1;
        }
        time = times [i]; //advance time
		//if the next time is out of range store the finalChar for rounding errors
		//if the state[] array reaches its Q before the stop time, finalChar retains its space value to fill the array with space chracters
        if (time >= stop) { 
            finalChar = currState;
        }
        currState = state[i]; //advance state
        i = i + 1;
    }
    while(j < numChar) { //finishes the history[] array after processing given data. accounts for rounding errors or when the ending time is after the largest time stamp
        history[j] = finalChar;
        j = j + 1;
    }
    cout << "\"" << history << "\"" << endl;
}