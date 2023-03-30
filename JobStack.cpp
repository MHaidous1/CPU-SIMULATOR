//
//  JobStack.cpp
//  CIS200_Project2
//
//  Created by Mohammed Haidous, Jamil Ahmad, Anthony Tenn on 11/18/22.
//

#include "Methods.h"

JobStack::JobStack() {
    jobArrived = 0;
}

// This Method adds a new job to the top of the stack
void JobStack::PushJobStack(Job inputJob) {
    jobArrived++;
    jobArr[jobArrived - 1] = inputJob;
}

// Method to remove the job on the top of stack and return it to the main Method
Job JobStack::RemoveJobStack() {
    Job jobTemp;
    jobTemp = jobArr[jobArrived - 1];
    jobArr[jobArrived - 1] = { '\0',0, 0, 0, 0 };
    jobArrived--;
    return jobTemp;
}

// Method to determine if stack is empty
bool JobStack::JobEmpty() {

    if (jobArrived == 0) { return true; }

    else {return false;}
}

// Method to determine if the job stack is full
bool JobStack::JobFull() {

    if (jobArrived == 5920) { return true; }
    else { return false; }
    
}

// Method to print out all jobs in the stack
void JobStack::PrintJobs() {
    
    for (int stackArr = jobArrived - 1; stackArr >= 0; stackArr--) {
            
            cout << "Type " << jobArr[stackArr].jobType << "   ";
            cout << "Arrival Time " << jobArr[stackArr].arrivalTime << "   ";
            cout << "Job Number " << jobArr[stackArr].jobNum << "   ";
            cout << "Type Number " << jobArr[stackArr].typeNum << "   ";
            cout << "Processing Time " << jobArr[stackArr].processTime << endl;
    }
}

// Method that returns to main the arrival time of the job on top of stack
int JobStack::PeekJobArrivalTime() { return jobArr[jobArrived - 1].arrivalTime; }
