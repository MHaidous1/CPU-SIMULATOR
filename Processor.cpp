//
//  Processor.cpp
//  CIS200_Project2
//
//  Created by Mohammed Haidous, Jamil Ahmad, Anthony Tenn on 11/18/22.
//

#include "Methods.h"

// Processor Constructor
Processor::Processor() {
    currentJob = { '\0', 0, 0, 0, 0 ,0 };
    jobArrived = 0;
}

// Method to add a job to the processor stack
void Processor::PushProcessor(Job inputJob) {

    if (jobArrived == 0) {
        currentJob = inputJob;
        jobArrived++;
    }
}

// Method to remove an item from processor stack
Job Processor::RemoveProcessor() {
    
    Job tempJob = currentJob;
    currentJob = {};
    jobArrived--;
    return tempJob;
}

// Method to check whether processor stack is empty
bool Processor::IsEmpty() {

    if (jobArrived == 0) { return true; }
    else { return false; }
}

// Method to check whether processor stack is full
bool Processor::IsFull() {
    if (jobArrived == 1) { return true; }
    else { return false; }
}


// Method to check when processor has no time remaining in stack
bool Processor::IsComplete() {

    if (currentJob.processTime == 0) { return true;}
    else { return false;}
}

//Decreases processing time in an active job
void Processor::LoadJob(){
    
    currentJob.processTime--;
}
