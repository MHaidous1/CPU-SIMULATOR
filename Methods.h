//
//  Methods.h
//  CIS200_Project2
//
//  Created by Mohammed Haidous, Jamil Ahmad, Anthony Tenn on 11/18/22.
//

#ifndef Methods_h
#define Methods_h

#include <stdio.h>
#include <iostream>

using namespace std;

struct Job {

    char jobType;
    int processTime;
    int typeNum;
    int jobNum;
    int arrivalTime;
    int waitTime = 0;
};

//Size of struct is 24
const int jobSize = sizeof(Job);

class JobStack {
    
private:
    Job jobArr[5920];
    int jobArrived;
    
public:
    //Constructor prototype
    JobStack();
    
    //Method to Push the Job Stack
    void PushJobStack(Job inputJob);
    
    //Method to remove a job from the stack
    Job RemoveJobStack();
    
    //Method to determine if job is empty
    bool JobEmpty();
    
    //Method to determine if job is full
    bool JobFull();
    
    //Method to print all jobs
    void PrintJobs();
    
    //Returns the arrival time of each job
    int PeekJobArrivalTime();
    
    // Inline GetCount method that returns jobArrived to main
    int GetJobArrived() { return jobArrived;}
    
};

//Class for Processor
class Processor {

private:
Job currentJob;
int jobArrived;

public:
    
    //Constructor
    Processor();
    
    //Method to add a job to the Processor Stack
    void PushProcessor(Job inputJob);
    
    //Method to remove an item from the Processor stack
    Job RemoveProcessor();
    
    //Method to check whether the Processor stack is full
    bool IsEmpty();
    
    //Methods to check whether the Processor stack is full
    bool IsFull();
    
    //Method to check when the processor has no time remaining in the stack, else not complete.
    bool IsComplete();
    
    //Method that decreases the processing time in an active job
    void LoadJob();
    
    // Inline  method definition that returns currentJob to main
    Job PeekJob() { return currentJob; }
};


class NewHeap {

    Job* heapArr;
    int amount;
    int sizeOfHeap;

public:
    // Constructor
    NewHeap(int capacity);

    void MinHeapSubTree(int);

    // In line method to return index of parent of node at the index
    int ParentNode(int i) { return (i - 1) / 2; }

    // In line method to return index of left child of node at the index
    int LeftNode(int i) { return (2 * i + 1); }

    // In line method to return index of right child of node at the index
    int RightNode(int i) { return (2 * i + 2); }

    // Method to extract minimum element of heap
    Job PullMin();

    // Method to return minimum heap
    Job GetMinHeap() { return heapArr[0]; }

    //Method to insert a new job key
    void InsertKey(Job k);

    //Method to check if the heap is empty
    bool IsHeapEmpty();

    //Method that swaps two elements in the heap
    void SwapHeap(Job* heapOne, Job* heapTwo);

    //Method that prints objects from Heap starting at root
    void PrintHeap();

    // Inline method to get heap size in main
    int SizeOfHeap() { return sizeOfHeap; }

    //Method that increases the wait time for objects in the queue
    void AddWaitTime();

    //Method that returns sum of wait times of object wait times
    int RemainingTime();
};

#endif
