/* @Author
Student Name: Şafak Özkan Pala  
Student ID : 150210016
Date: 29.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string>
#include "ProcessRep.h"


using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime)
{   // initializing variables with proper values.
    this->mProcessType = processType;
    this->mProcessID = processID;
    this->mDeliverTime = deliverTime;
    this->mProcessTime = processTime;
    this->mpNext = NULL;
    this->startTime = -1;
    this->endTime = -1;
    this->remainingTime = processTime;
}

ProcessRep::~ProcessRep()
{
    // setting an unusuable pointer to null.
    this->mpNext = NULL;
}

ProcessRep* ProcessRep::getNext()
{
    // getting the private variable mpnext.
    return this->mpNext;
}

void ProcessRep::setNext(ProcessRep *next)
{
    //setting a new value to privaet valiable mpnext.
    this->mpNext = next;
}

string ProcessRep::getProcessType()
{
    //getting the private valiable mProcessType.
    return this->mProcessType;
}

void ProcessRep::setProcessType(string processType)
{
    //setting a new value to privaet valiable mProcessType.
    this->mProcessType = processType;
}

int ProcessRep::getDeliverTime()
{
    // getting the private variable mDeliverTime.
    return this->mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime)
{
    //setting a new value to privaet valiable mDeliverTime.
    this->mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID()
{
    // getting the private variable mProcessID.
    return this->mProcessID;
}

void ProcessRep::setProcessID(int processID)
{
    //setting a new value to privaet valiable mProcessID.
    this->mProcessID = processID;
}

int ProcessRep::getProcessTime()
{
    // getting the private variable mProcessTime.
    return this->mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime)
{
    //setting a new value to privaet valiable mProcessTime.
    this->mProcessTime = ProcessTime;
}