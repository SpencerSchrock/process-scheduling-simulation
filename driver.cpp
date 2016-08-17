// A quick driver to test the History Display routine
// It just fabricates a single job history to see what it does
//
#include <iostream>
using namespace std;

#include "histo.h"

int main()
{
    
    int  times1[] = { 500, 1100, 1220, 1420, 1460, 1600, 1700 };
    char state1[] = { '-', '-', 'D', 'X', 'N', 'X', 'Q' };
    
    cout << "1000 to 1500" << endl;
    displayHistory( state1, times1, 1000, 1500 );
    
   int times[] = { 100, 250, 355, 370, 460, 600 };
   char state[] = { 'X', '-', 'X', '-', 'X', 'Q' };
 
   cout << "100 to 600" << endl;
   displayHistory( state, times, 100, 600 );  
   cout << endl << "300 to 400" << endl;
   displayHistory( state, times, 300, 400 );  
   cout << endl << "0 to 1000" << endl;
   displayHistory( state, times, 0, 1000 );
    cout << endl << "0 to 2000" << endl;
    displayHistory( state, times, 0, 2000 );
   cout << endl << "350 to 375" << endl;
   displayHistory( state, times, 350, 375 );

}

