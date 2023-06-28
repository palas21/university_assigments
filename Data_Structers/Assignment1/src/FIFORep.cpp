/* @Author
Student Name: Şafak Özkan Pala  
Student ID : 150210016
Date: 29.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    //initializing a single linked list with no element. 
    this->mpHead = NULL;
    this->mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep* head)
{
    //initializing a single linked list with one element and setting its tail and head to this element.
    this->mpHead = head;
    this->mpTail = head;
}

FIFORep::~FIFORep()
{
    /*
    starting with the head, we delete every element of the list.
    */
    ProcessRep* temp = mpHead; // creating a temp and point it to the head.

    while(this->mpHead != NULL){ // until head is NULL we keep doing that assigning temp to the next element, deleting head and assigning head to the temp.
        temp = this->mpHead->getNext();
        delete this->mpHead;
        this->mpHead = temp;
    }
    this->mpTail = NULL; // after deleting all the element of the list and our head is now NULL we set tail to NULL to avoid problems.
    delete temp; // we finished all the operation with temp so we no longer need it. 
    temp = NULL;    // assigning to the NULL to avoid reaching deleted memory.
}

void FIFORep::setHead(ProcessRep* head)
{
    // setting head to new value
    this->mpHead = head;
}

ProcessRep* FIFORep::getHead()
{
    //getting head's value 
    return this->mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
    //setting tail to the new value.
    this->mpTail = tail;
}

ProcessRep* FIFORep::getTail()
{
    //getting tail's value.
    return this->mpTail;
}

void FIFORep::queue(ProcessRep* p)
{

    if(this->mpTail == NULL){ // if our list is empty we make p to our first element and assign head and tail to this pointer.
        this->mpHead = p;
        this->mpTail = p;
        this->mpTail->setNext(NULL); // since there is not a next element we assign this value to NULL;
    }
    else{ // if our list is not empty.
    this->mpTail->setNext(p); // we make tail's next element to this pointer.
    this->mpTail = p; // since there is a new element, we make our tail to that next element.
    this->mpTail->setNext(NULL); // since there is not a next element after our tail we make setnext pointer to NULL.
    }

    /*
        The function add a process to the tail of the queue.
    */
}

ProcessRep* FIFORep::dequeue()
{   
    if(this->mpHead == NULL){ // if our list is empty we return NULL.
        return NULL;
    }
    else{ // if list is not empty
        ProcessRep* temp = this->mpHead; // we create a tempature element and assigning it to first element of the list.
        if(this->mpHead->getNext() == NULL){ // if list has only one element we make our list empty after dequeuing that one element.
            this->mpHead = NULL; // since list is empty now we make our head and tail NULL.
            this->mpTail = NULL;
        }else{ // if list has more than one element 
            this->mpHead = this->mpHead->getNext(); // we make our head to second element of the list.
        }   
        temp->setNext(NULL); // we set dequeued element's next to NULL to avoid problems.
        return temp; 
    }
    /*
        "The function removes a process from the HEAD of the FIFO and returns it. If there is no item, it returns NULL"
    */   
}

ProcessRep* FIFORep::searchID(int id) 
{   
    ProcessRep* temp = this->mpHead;// we are making a temporary element and assign it to the head.
    
    if(temp == NULL){ //if there is no element in the list we return NULL. 
        return NULL;
    }

    while(temp->getNext() != this->mpTail){ // until we reach the tail of the list we search through list.
        if(temp->getProcessID() == id){ // if our temp's id equal to given id we return temp.
            return temp;
        }
        else{ // if it is not equal we move to the next element of the list.
            temp = temp->getNext();
        }
    }
    if(temp->getProcessID() == id){ // we search tail for the given id
            return temp;
    }
    // if there is no match we return NULL.
    return NULL;

    /*
        "search the list for a given process ID."
    */ 
}

void FIFORep::printFIFO()
{
    ProcessRep* temp = this->mpHead; // we make a temporary element and assign it to headof the list.
    if(temp != NULL){ // if list is not empty we print the list.
        while(temp != mpTail){ // we print the temp and assign temp to the next element of the list until the tail. 
            cout<< temp->getProcessType() << temp->getProcessID() << " " << temp->startTime << " " << temp->endTime << " ";
            temp = temp->getNext();
        }// we print the tail.
        cout<< temp->getProcessType() << temp->getProcessID() << " " << temp->startTime << " " << temp->endTime << " ";
    }
    
    /*
        <Process Type><ID><" "><start Time><" "><Finish Time><" ">
        The function prints the proceses in the queue starting from Head to tail.
    */
}