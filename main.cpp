//
//  main.cpp
//  CIS200_Project2
//
//  Created by Mohammed Haidous, Jamil Ahmad, & Anthony Tenn on 11/18/22.
//

#include <random>
#include <fstream>
#include <iostream>
#include "Methods.h"
using namespace std;

// Function prototype to create the job stack
void CreateJobs(JobStack& inputJobs);

int main() {
    
    //Objects
    JobStack inputJobs;
    NewHeap jobTotal(5920);

    //output file of log actions
    ofstream logFile;
    logFile.open("log.txt");

    long double totalAvg = 0;
    int maxQueue = 0;
    long int idleIteration = 0;
    int jobsCompleted = 0;
    int jobA_Completed = 0, jobB_Completed = 0, jobC_Completed = 0, jobD_Completed = 0;
    int jobA_Arrived = 0, jobB_Arrived = 0, jobC_Arrived = 0, jobD_Arrived = 0;
    int currentCycle = 0;
    int totalProcessingTime = 0;
    int totalWaitTime = 0;
    float averageWaitTime = 0;
    int userCPU;

    CreateJobs(inputJobs);
    //8
    inputJobs.PrintJobs();

    cout << endl;
    
    //org.dat is the organized file from the other program
    fstream jobFile("org.dat", ios::in | ios::ate | ios::binary);

    //File validation
    if (!jobFile){
        cerr << "org.dat could not be opened" << endl;
        return -1;
    }

    do {
        cout << "Please input a number of processors you'd like to use:" << endl;
        cin >> userCPU;
        //Validation loop
        while(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Please enter a valid integer.\n";
            cin >> userCPU;
            
        }
        //Ensuring user input is > then 0
        if (userCPU < 0) {
            cout << "Invalid Input" << endl;
        }
    } while (userCPU < 1);

    Processor* CPU = new Processor[userCPU];

    // Main loop that runs for 500 time units and runs an additional 9500 time units before final metrics report
    for (int time = 1; time <= 10000; time++){
    
        //Reporting time
        logFile << "Time " << time << ": ";

        // Finishes a jobs and outputs the completion status of that individual job
        for (int x = 0; x < userCPU; x++){
            
            if (CPU[x].IsComplete() && CPU[x].IsFull()){

                Job tempJob;
                tempJob = CPU[x].RemoveProcessor();

                logFile << "Job " << tempJob.jobType << " " << tempJob.typeNum << " Completed; ";
                jobsCompleted++;

                if (tempJob.jobType == 'A') {

                    jobA_Completed++;
                }

                if (tempJob.jobType == 'B') {

                    jobB_Completed++;
                }

                if (tempJob.jobType == 'C') {

                    jobC_Completed++;
                }

                if (tempJob.jobType == 'D') {

                    jobD_Completed++;
                }

            }
        }

        // Adds items to the heap
        while (inputJobs.PeekJobArrivalTime() == time) {

            Job tempJob = inputJobs.RemoveJobStack();

            jobTotal.InsertKey(tempJob);

            logFile << "Arrival Job " << tempJob.jobType << ": Overall Job " << tempJob.jobNum
                << ", Job " << tempJob.jobType << " " << tempJob.typeNum
                << ", Processing Time " << tempJob.processTime << "; ";


            // Counts each type of job in each run
            if (tempJob.jobType == 'A') {
                jobA_Arrived++;
            }

            if (tempJob.jobType == 'B') {
                jobB_Arrived++;
            }

            if (tempJob.jobType == 'C') {
                jobC_Arrived++;
            }

            if (tempJob.jobType == 'D') {
                jobD_Arrived++;
            }
        }


        // Removes a job D from the stack for a more priority job
        for (int cpuNum = 0; cpuNum < userCPU; cpuNum++) {

            if (CPU[cpuNum].IsEmpty() || jobTotal.SizeOfHeap() == 0) {

                continue;
            }

            Job temp = jobTotal.GetMinHeap();

            if (temp.jobType == 'D') {

                Job interruptedJob;
                Job Djob;
                interruptedJob = CPU[cpuNum].RemoveProcessor();
                Djob = jobTotal.PullMin();
                CPU[cpuNum].PushProcessor(Djob);
                jobTotal.InsertKey(interruptedJob);
            }
            else {
                break;
            }
        }

        // Processes a new cpu in stack and adds to processing time
        for (int x = 0; x < userCPU; x++) {

            if (jobTotal.IsHeapEmpty()){
                
                logFile << "Queue: Empty; ";

                break;
            }

            else if (CPU[x].IsEmpty()){
                
                Job tempJob = jobTotal.PullMin();
                totalWaitTime = totalWaitTime + tempJob.waitTime;
                tempJob.waitTime = 0; // Resets job wait time
                CPU[x].PushProcessor(tempJob);

                logFile << "Begin Processing Job " << tempJob.jobType << " " << tempJob.typeNum
                    << " in CPU " << x + 1 << " , End Time " << time + tempJob.processTime << "; ";
            }
        }

        //Process
        bool activeJob = false;

        for (int x = 0; x < userCPU; x++){

            if (CPU[x].IsEmpty()){

                logFile << " CPU " << x + 1 << ": Idle Time " << idleIteration;
                idleIteration++;

            }

            else {

                Job tempJob = CPU[x].PeekJob();
                CPU[x].LoadJob();
                activeJob = true;

                logFile << "CPU " << x + 1 << ": Job " << tempJob.jobType << " " << tempJob.jobNum << "; ";
                totalProcessingTime++;

            }
        }

        jobTotal.AddWaitTime();

        if (activeJob == true){
            
            currentCycle++;
        }

        totalAvg = totalAvg + (jobTotal.SizeOfHeap() - totalAvg) / time;

        if (jobTotal.SizeOfHeap() > maxQueue)

            maxQueue = jobTotal.SizeOfHeap();

        logFile << endl;


        //Initial Metrics Analysis
        if (time == 500){
            
            int totalJobsArrived = jobA_Arrived + jobB_Arrived + jobC_Arrived + jobD_Arrived;
            totalWaitTime = totalWaitTime + jobTotal.RemainingTime();
            averageWaitTime = totalWaitTime / totalJobsArrived;

            cout << endl <<  "Initial Metrics Report: " << endl;
            cout << "Number of processor(s) being used: " << userCPU << endl;
            cout << "Current Queue Size: " << jobTotal.SizeOfHeap() << endl;
            cout << "Average queue size: " << totalAvg << endl;
            cout << "Maximum jobs in queue: " << maxQueue << endl;
            cout << "Total time jobs were in queue: " << totalWaitTime << " time units." << endl;
            cout << "Average time jobs are in queue: " << averageWaitTime << " time units" << endl;
            cout << "Total number of jobs A arrived: " << jobA_Arrived << endl;
            cout << "Total number of jobs A completed: " << jobA_Completed << endl;
            cout << "Total number of jobs B arrived: " << jobB_Arrived << endl;
            cout << "Total number of jobs B completed: " << jobB_Completed << endl;
            cout << "Total number of jobs C arrived: " << jobC_Arrived << endl;
            cout << "Total number of jobs C completed: " << jobC_Completed << endl;
            cout << "Total number of jobs D arrived: " << jobD_Arrived << endl;
            cout << "Total number of jobs D completed: " << jobD_Completed << endl;
            cout << "Total jobs completed: " << jobsCompleted << endl;
            cout << "Total time CPU(s) were processing: " << totalProcessingTime << " time units" << endl;
            cout << "Total time CPU(s) were idle: " << idleIteration << " time units." << endl << endl;
        }
    }

    // Metrics for final analysis
    int totalJobsArrived = jobA_Arrived + jobB_Arrived + jobC_Arrived + jobD_Arrived;
    totalWaitTime = totalWaitTime + jobTotal.RemainingTime();
    averageWaitTime = totalWaitTime / totalJobsArrived;

   
    cout << endl << "Final Metrics Report: " << endl;
    cout << "Number of processor(s) being used: " << userCPU << endl;
    cout << "Final Queue Size: " << jobTotal.SizeOfHeap() << endl;
    cout << "Average queue size: " << totalAvg << endl;
    cout << "Maximum jobs in queue: " << maxQueue << endl;
    cout << "Total time jobs were in queue: " << totalWaitTime << " time units." << endl;
    cout << "Average time jobs are in queue: " << averageWaitTime << " time units" << endl;
    cout << "Total number of jobs A arrived: " << jobA_Arrived << endl;
    cout << "Total number of jobs A completed: " << jobA_Completed << endl;
    cout << "Total number of jobs B arrived: " << jobB_Arrived << endl;
    cout << "Total number of jobs B completed: " << jobB_Completed << endl;
    cout << "Total number of jobs C arrived: " << jobC_Arrived << endl;
    cout << "Total number of jobs C completed: " << jobC_Completed << endl;
    cout << "Total number of jobs D arrived: " << jobD_Arrived << endl;
    cout << "Total number of jobs D completed: " << jobD_Completed << endl;
    cout << "Total jobs completed: " << jobsCompleted << endl;
    cout << "Total time CPU(s) were processing: " << totalProcessingTime << " time units" << endl;
    cout << "Total time CPU(s) were idle: " << idleIteration << " time units." << endl << endl;

    logFile.close();
    jobFile.close();
    return 0;
}

// Function defeinition to create the job stack
void CreateJobs(JobStack& inputJobs) {

    JobStack tempJobs;
    int jobArrived = 0;

    Job temp = { '\0', 0,0,0,0,0 };

    fstream jobFile("org.dat", ios::in | ios::ate | ios::binary); //org.dat is the organized file from the other program

    if (!jobFile){
        
        cerr << "org.dat could not be opened" << endl;
    }

    jobFile.seekg(0, ios::end);

    //add jobs from org.dat to stack
    for (int i = 0; i < 5920; i++)
    {
        static int jobNum = 1;
        
        //reset for next jobs
        temp = { '\0', 0, 0, jobNum, 0, 0 };

        jobFile.seekg((static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(i) * jobSize), ios::beg);
        jobFile.read((char*)&temp, jobSize);

        tempJobs.PushJobStack(temp);
        jobArrived++;
    }

    while (tempJobs.JobEmpty() != true) {

        inputJobs.PushJobStack(tempJobs.RemoveJobStack());
    }
    jobFile.close();
}
