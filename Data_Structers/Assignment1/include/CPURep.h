/* @Author
Student Name: Şafak Özkan Pala  
Student ID : 150210016
Date: 29.10.2022
*/

#ifndef _CPUREP
#define _CPUREP

#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

class CPURep
{
    /*
        The CPU representation class that run  processes.
    */  
private:
    FIFORep* mFinishedProcess;
public:
    CPURep();
    ~CPURep();

    FIFORep* getFinishedProcess();
    void setFinishedProcess(FIFORep*);

    ProcessRep* runCPU(ProcessRep*, int);
};

#endif