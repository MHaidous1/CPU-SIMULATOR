//
//  NewHeap.cpp
//  CIS200_Project2
//
//  Created by Mohammed Haidous, Jamil Ahmad, Anthony Tenn on 11/18/22.
//


#include "Methods.h"

//#include "JobStack.hpp"
// Constructor: Builds a heap from an input array of size cap
NewHeap::NewHeap(int cap){

    sizeOfHeap = 0;
    amount = cap;
    heapArr = new Job[cap];
}

// Method to insert a new job key
void NewHeap::InsertKey(Job k) {

    if (sizeOfHeap == amount) {

        cout << endl << "Overflow: Could not insertKey" << endl;
        return;
    }

    // inserts new key at the end
    sizeOfHeap++;
    int i = sizeOfHeap - 1;
    heapArr[i] = k;

    // If min heap found
    while (i != 0 && (heapArr[ParentNode(i)].processTime > heapArr[i].processTime || heapArr[i].jobType == 'D')) {
        
            SwapHeap(&heapArr[i], &heapArr[ParentNode(i)]);
            i = ParentNode(i);
    }

    // Executes if element isn't swapped out
    if (i == 0) {

        if (sizeOfHeap > 1 && (heapArr[1].processTime < heapArr[0].processTime || heapArr[1].jobType == 'D')) {

            SwapHeap(&heapArr[1], &heapArr[0]);
        }

        if (sizeOfHeap > 2 && (heapArr[2].processTime < heapArr[0].processTime || heapArr[2].jobType == 'D')) {

            SwapHeap(&heapArr[2], &heapArr[0]);
        }
    }
}

// Method to check if heap is empty
bool NewHeap::IsHeapEmpty() {

    if (sizeOfHeap == 0) { return true; }
    else { return false; }
}

// Swaps two elements in heap
void NewHeap::SwapHeap(Job* heap1, Job* heap2) {

    Job temp = *heap1;
    *heap1 = *heap2;
    *heap2 = temp;

}

// Prints objects in from Heap starting at root
void NewHeap::PrintHeap() {

    for (int arr_i = 0; arr_i < sizeOfHeap; arr_i++) {

        cout << "Type " << heapArr[arr_i].jobType << "   ";
        cout << "Arrival Time " << heapArr[arr_i].arrivalTime << "   ";
        cout << "Job Number " << heapArr[arr_i].jobNum << "   ";
        cout << "Type Number " << heapArr[arr_i].typeNum << "   ";
        cout << "Processing Time " << heapArr[arr_i].processTime << endl;
        
    }
}

//Method that increases wait time in all job objects within queue
void NewHeap::AddWaitTime() {

    if (sizeOfHeap > 0) {

        for (int arr_i = 0; arr_i < sizeOfHeap; arr_i++) {

            heapArr[arr_i].waitTime++;
        }
    }

}

//Returns sum of wait times of all job objects
int NewHeap::RemainingTime() {

    int totalWait = 0;
    if (sizeOfHeap > 0) {

        for (int arr_i = 0; arr_i < sizeOfHeap; arr_i++) {

            totalWait = totalWait + heapArr[arr_i].waitTime;
        }
    }
    return totalWait;
}

// Method to remove minimum element or root from min heap
Job NewHeap::PullMin(){

    if (sizeOfHeap <= 0) {

        return { '\0',0,0,0,0 };
    }

    if (sizeOfHeap == 1) {

        sizeOfHeap--;
        return heapArr[0];
    }

    // Store the minimum value, and remove it from heap
    Job root = heapArr[0];
    heapArr[0] = heapArr[sizeOfHeap - 1];
    sizeOfHeap--;
    MinHeapSubTree(0);

    return root;
}

// Recursive Method to heapify a subtree with root at given index
void NewHeap::MinHeapSubTree(int i) {

    int left = LeftNode(i);
    int right = RightNode(i);
    int smallest = i;
    if (left < sizeOfHeap && heapArr[left].processTime < heapArr[i].processTime) {

        smallest = left;
    }

    if (right < sizeOfHeap && heapArr[right].processTime < heapArr[smallest].processTime) {

        smallest = right;
    }
    if (smallest != i) {

        SwapHeap(&heapArr[i], &heapArr[smallest]);
        MinHeapSubTree(smallest);
    }
}
