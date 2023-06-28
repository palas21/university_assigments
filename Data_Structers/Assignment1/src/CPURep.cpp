/* @Author
Student Name: Şafak Özkan Pala  
Student ID : 150210016
Date: 29.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    //we create a single linked list to keep finished processes.
    this->mFinishedProcess = new FIFORep();
}

CPURep::~CPURep()
{
    // we delete linked list to free the memory.
    delete this->mFinishedProcess;
    // assign this pointer to NULL to avoid problems.
    mFinishedProcess = NULL;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{   
   
    if(p->remainingTime == p->getProcessTime()){  //we check for that if this is the first run or not. If it is, assign the time to its start time.
        p->startTime = time;
    }
    p->remainingTime--; // we decrease the remaining time for the finish the process.
    if(p->remainingTime == 0){ // if process is finished 
        p->endTime = ++time; // we assign its endtime 
        this->mFinishedProcess->queue(p); // and send it to the finished process list.
        return NULL; // and return NULL because this process is finished we no longer put it in an another queue.
    }
    else{
        // we return this process to put it in a queue.
        return p;
    }
    /*
        (int time) argument is used for defining the endTime of the process. 
        the CPURep objects keep the finished process. 
        If a process is completed, it will not return to the scheduler; 
        the runCPU function saves the finished process into mFinishedProcess with endTime.
    */
}

FIFORep* CPURep::getFinishedProcess()
{
    // we get finished process list.
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    // we set finished process list.
    this->mFinishedProcess = finishedProcess;
}