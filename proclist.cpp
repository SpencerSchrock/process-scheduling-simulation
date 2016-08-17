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
   if (head == NULL)		// no list yet
	   head = newEle;
   else
	   tail->next = newEle;	// add to end of list
   tail = newEle;
}

//  remove the element at the front end of the list
//  Two reference parameters are provided to hold onto information
//  from the removed element.  The time index is considered unnecessary.
void ProcList::popFront( int &procId, char &state )
{
	if (head != NULL)		// if list non-empty list
	{
		ProcListElement *removal = head;	// element to be removed
		procId = head->procID; //store pid
		state = head->state; //store state
		head = head->next;	// update new head
		delete removal;		// deallocate removed element
	}
	else
		procId = -1; //empty list, indicate with invalid pid
}

//  adds a new element into a sorted linked list
//  which is sorted in increasing order according to the 'time' argument
void ProcList::insert( int procId, int time, char state )
{
   ProcListElement *newEle = new ProcListElement( procId, time, state );
   ProcListElement *curr = head;
    if ( head == NULL || time < head->time ) //if element needs to be inserted at front
    {
        newEle->next = head;
        head = newEle;
    }
    else { //add to after existing element
        while( curr->next != NULL && curr->next->time < time)
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
    ProcListElement *curr; //stores the pointer to the current node
    ProcListElement *removal; //element to be removed
    //case 1 loop for removing head. as long as the head is a unneeded time remove it
    while (head != NULL && head->next != NULL && head->time == head->next->time) {
        removal = head;
        head=head->next;
        delete removal;
    }
    
	curr = head; //set the loop variable to loop through for case 1

    while(curr != NULL && curr->next != NULL){ //case 1, loop through log history
        //while the next and next-next elements are duplicates, remove the first one
        while (curr->next->next != NULL && curr->next->time == curr->next->next->time){
            removal = curr->next;
            curr->next = curr->next->next;
            delete removal;
        }
        curr = curr->next;
    }
    
    curr = head; //reset the loop variable to loop through for case 2

    while(curr != NULL && curr->next != NULL) { //case 2, go through log history
        //as long as the states are the same remove the second one
        while (curr->next != NULL && curr->state == curr->next->state) {
            removal = curr->next;
            curr->next = curr->next->next;
            delete removal;
        }
        curr = curr->next;
    }
}