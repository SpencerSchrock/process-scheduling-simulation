#include <iostream>
using namespace std;

// List of Process ProcList Information
// This is a simple linked list, all of whose elements record
// information about a process in a simulated process scheduler.
// This list data structure will be used for three different purposes:
// -- a record of the past history of a particular process
// -- a collection for the job scheduler of processes currently wishing to run
// -- a task list for known future events for the simulation

#include "proclist.h"

// First, some helper functions to display the data

ostream &operator<<( ostream &stream, ProcListElement &ele )
{
   stream << "(" << ele.procID << "," << ele.state << "," 
	  << ele.time << ")";
   return stream;
}

ostream &operator<<( ostream &stream, ProcList &hist )
{
   for (ProcListElement *curr = hist.head; curr != NULL; curr = curr->next )
	stream << *curr;
   stream << endl;
   return stream;
}

// And some functionality for the list itself.
// First some easy iterator definitions:
ProcIterator ProcList::begin()
{
    return ProcIterator( this, head );
}

ProcIterator ProcList::end()
{
    return ProcIterator( this, NULL );
}

//  push a new element to the back end of the list
//  Primarily used for First-In, First-Out ordering
void ProcList::pushBack( int procId, int time, char state )
{
   ProcListElement *newEle = new ProcListElement( procId, time, state );
   if (head == NULL)		// if no list yet
	   head = newEle;		//    start with this one
   else
	   tail->next = newEle;	// or last element now has a successor
   tail = newEle;
}

//  remove the element at the front end of the list
//  Two reference parameters are provided to hold onto information
//  from the removed element.  The time index is considered unnecessary.
void ProcList::popFront( int &procId, char &state )
{
	if (head != NULL)		// can only remove from non-empty list
	{
		ProcListElement *removal = head;	// remember what is being removed
		procId = head->procID;
		state = head->state;
		head = head->next;	// the second item is now first
		delete removal;		// deallocate expired element
	}
}

//  adds a new element into a sorted linked list
//  which is sorted in increasing order according to the 'time' argument
void ProcList::insert( int procId, int time, char state )
{
   ProcListElement *newEle = new ProcListElement( procId, time, state );
   ProcListElement *curr = head;
    if (head == NULL) {
        head = newEle;
    }
    else {
        while( curr->next != NULL && time > curr->next->time)
            curr = curr->next;
        newEle->next = curr->next;
        curr->next = newEle;
    }
}

// EXTRA CREDIT
// Condenses the information in the linked list after it is collected.
// 1) If two adjacent cells have the same time information,
//    the first can be removed (did not actually occupy that state)
// 2) If two adjacent cells have the same state recorded,
//    the second can be removed (did not actually change state)
void ProcList::condense()
{
}
