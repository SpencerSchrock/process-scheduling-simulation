#include "process.h"

// History Displayer
// Produces an Ascii-graphic representation of the history for processes
// within a simulation of job scheduling.  Each history is recorded as a
// series of time stamps, represented here as integer time values and
// characters representing state.
// Paramaters:
//     history  input Process array	objects containing linked lists
//     					with the times and states
//     					(see process.h)
//     size	input int		number of processes (rows of output)
//     start	input int		beginning of time frame of interest
//     stop	input int		end of time frame of interest
// Pre-Conditions:
//     each linked list concludes with an entry with state 'Q' for completion
//     'start' and 'stop' are both positive integers, with start < stop
//     NOTE:   'start' or 'stop' may be outside the time ranges in the history
// Results:
//     A display of between 20 and 50 printable characters representing
//     the job history within the time range of interest, using the
//     characters stored within the given list.  Events outside the actual range
//     of the job history will be displayed with blanks.
void displayHistory( Process history[], int size, int start, int stop );
