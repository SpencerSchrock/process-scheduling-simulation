// History Displayer
// Produces an Ascii-graphic representation of the history of a process
// within a simulation of job scheduling.  The history is recorded as a
// series of time stamps, represented here as integer time values and
// characters representing state.
// Paramaters:
//     state	input char array	what state this job changed to
//     times	input int array		when this job changed state
//     start	input int		beginning of time frame of interest
//     stop	input int		end of time frame of interest
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
void displayHistory( const char state[], const int times[], int start, int stop );
