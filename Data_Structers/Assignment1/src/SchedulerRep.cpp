/* @Author
Student Name: Şafak Özkan Pala  
Student ID : 150210016
Date: 29.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    for(int i = 0; i < 3;i++){  //we create 3 single linked list.
        this->mpProcessFIFO[i] = new FIFORep();
    }
    this->mpRunningProcess = NULL; // assign pointer to NULL to avoid problems.
    this->pCpuObj = new CPURep(); // we create a cpu object.
    this->totalTime = 0; // we start with time 0.
    this->timeSliceCount = 0; // we start with timeSliceCount 0.
}
SchedulerRep::~SchedulerRep()
{
    for(int i = 0; i < 3; i++){ // we delete 3 single linked list and assign their pointers to NULL to avoid problems.
        delete this->mpProcessFIFO[i];
        this->mpProcessFIFO[i] = NULL;
    }    
    delete this->pCpuObj; // we delete cpu object and assign it to NULL to avoid problems.
    this->pCpuObj = NULL; 
    this->mpRunningProcess = NULL; // we assign mpRunningProcess pointer to NULL to avoid problems. 

    
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
    //we get the single linked list of given index. 
    return this->mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    //we set the single linked list to given fifo.
    this->mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    //we set mpRunningProcess to the given pointer.
    this->mpRunningProcess = p;
}

ProcessRep* SchedulerRep::getRunningProcess()
{
    // we get the mpRunningProcess
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
    // we separete 3 linked list to their priaority in order to A>B>C and add the new coming pointer to its appropriate list.
    if(p->getProcessType() == "A"){
        this->mpProcessFIFO[0]->queue(p);
    }
    if(p->getProcessType() == "B"){
        this->mpProcessFIFO[1]->queue(p);
    }
    if(p->getProcessType() == "C"){
        this->mpProcessFIFO[2]->queue(p);
    }
/*
    It adds the new process to the end of the appropriate FIFO.
    YOUR CODE HERE 
*/
}

ProcessRep* SchedulerRep::popProcess()
{
    // we get a process in order to its priaority. 

    ProcessRep  *temp = this->mpProcessFIFO[0]->dequeue();
    if(temp == NULL){ // If A list is empty we try to get process from B. 
        temp = this->mpProcessFIFO[1]->dequeue();
    }
    if(temp == NULL){ // If B list is empty we try to get process from C. 
        temp = this->mpProcessFIFO[2]->dequeue();
    }    
    //If all three list empty we already have a NULL pointer from the 87th line and return it.
    return temp;

/*
    It removes a process from the beginning of the FIFOs according to the scheduler rule and returns it.
*/
}

bool SchedulerRep::checkTimeSlice()
{
    if (this->getRunningProcess() != NULL) // if we have a running process
    {
        if (this->getRunningProcess()->getProcessType() == "A" && this->timeSliceCount == 2) // if its type A and it reach its maximum value we return false to send it back to queue.
        {
            return false;
        }
        if (this->getRunningProcess()->getProcessType() == "B" && this->timeSliceCount == 4) // if its type B and it reach its maximum value we return false to send it back to queue.
        {
            return false;
        }
        if (this->getRunningProcess()->getProcessType() == "C" && this->timeSliceCount == 8) // if its type C and it reach its maximum value we return false to send it back to queue.
        {
            return false;
        }
    }
    // if it didn't reach its maximum value than we keep doing that process until more prioarity process come to the queue.
    return true;
}

ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){
    // we send process pointer to the cpu and return it.
    return this->pCpuObj->runCPU(p,this->totalTime);
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{
    /*
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run.
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will
                be put back to the queue first.


    */

   
    ProcessRep *temp = new ProcessRep(type,id,arrivalTime,processTime); // we create a temporary process to keep new process.
    this->pushProcess(temp); // we send it to the queue.
    
    if(this->mpRunningProcess == NULL){ // if there is no running process we get a new process and start the timeslicecount zero.
        this->mpRunningProcess = this->popProcess();
        this->timeSliceCount = 0;
    }
    else{ // if there is a running process we get both running process's type and newcoming procecess's.
        int new_coming,current_one;
        if(type == "A"){
            new_coming = 2;
        } 
        if(type == "B"){
            new_coming= 1;
        }
        if(type == "C"){
            new_coming = 0;
        }
        if(this->mpRunningProcess->getProcessType() == "A"){
            current_one = 2;
        }
        if(this->mpRunningProcess->getProcessType() == "B"){
            current_one = 1;
        }
        if(this->mpRunningProcess->getProcessType() == "C"){
            current_one = 0;
        }
        // we give each type a value to compare their priaorities.

        if(false == this->checkTimeSlice()){ // if the running process finised.
            this->pushProcess(this->mpRunningProcess); // we send back running process to queue and get a new one and start the timslice from 0.
            this->setRunningProcess(this->popProcess());
            this->timeSliceCount = 0;
        }
        else{ // if the running process finished.
            if(new_coming > current_one){ // we check for priaorities. If new coming's type is more priority than running one  .
                this->pushProcess(this->getRunningProcess()); //we send running to queue
                this->setRunningProcess(this->popProcess()); //get new coming from the queue
                this->timeSliceCount = 0; // and start timeslicecount from the 0.
            }
        }
    }
    // we send running process to cpu.
    this->setRunningProcess(this->sendProcessToCPU(this->mpRunningProcess));
    
    // if running process is not finished we increase timslicecount.
    if(this->mpRunningProcess != NULL){ 
        this->timeSliceCount++;
    }
    else{  // running process is finished we get a new process and start timeslicecount from 0.
        this->mpRunningProcess = this->popProcess();
        this->timeSliceCount = 0;
    }
    // we increase total time after every process.
    temp = NULL;
    delete temp;
   this->totalTime++;
}

void SchedulerRep::schedule(ProcessRep* p)
{
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.

            The function takes only NULL as input to take the simulation one step forward according to schedule rules.


    */
   
    if(false == this->checkTimeSlice()) //if the timeslicecount is finihed 
    { 
        this->pushProcess(this->getRunningProcess()); // send running process to queue.
        this->setRunningProcess(this->popProcess()); // get a new process.
        this->timeSliceCount = 0; // set timslicecount 0.
    }

   if(this->getRunningProcess() != NULL){ // if there is running process
        this->setRunningProcess(this->sendProcessToCPU(this->mpRunningProcess)); // we send it to the cpu.
        if(this->getRunningProcess() != NULL){ // if it is not finished
            this->timeSliceCount++; // increase timslicecount.
        }   
        else{// if it is finished
            this->setRunningProcess(this->popProcess()); // get a new process.
            this->timeSliceCount = 0; // make timeslicecount zero.
        }
   }
// increase total time after every process.
   this->totalTime++;
}
