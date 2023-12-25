#ifndef __PROCESS_CONTROL_BLOCK_H
#define __PROCESS_CONTROL_BLOCK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
const int RESOURCE_TYPES = 5;
const int PROCESS_NUMS = 5;

// Process Control Block (PCB) structure
struct PCB
{
    int id;
    int priority;
    int cpuTime;
    int allTime;
    std::string state;
    int waitingTime;    // Added for performance metrics
    int turnaroundTime; // Added for performance metrics
    int submissionTime;
    int allocation[RESOURCE_TYPES];
    int claim[RESOURCE_TYPES];
};

void InitializeProcesses(std::vector<PCB> &processes, int n);
void DisplayCPUUsage(const std::vector<PCB> &processes);
void DisplayResourceUsage(const std::vector<PCB> &processes);
void PriorityScheduling(std::vector<PCB> &processes, bool display = false);
void RoundRobinScheduling(std::vector<PCB> &processes, bool display = false, int timeSlice = 1);
void HRRNScheduling(std::vector<PCB> &processes, bool display = false);
#endif