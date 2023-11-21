#ifndef __PROCESS_CONTROL_BLOCK_H
#define __PROCESS_CONTROL_BLOCK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

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
};

void initializeProcesses(std::vector<PCB> &processes, int n);
void displayProcesses(const std::vector<PCB> &processes);
void priorityScheduling(std::vector<PCB> &processes, bool display = false);
void roundRobinScheduling(std::vector<PCB> &processes, int timeSlice = 1, bool display = false);
void hrrnScheduling(std::vector<PCB> &processes, bool display = false);
bool isSafeState(const std::vector<std::vector<int>> &max, const std::vector<std::vector<int>> &allocation,
                 const std::vector<int> &available, std::vector<int> &work, std::vector<bool> &finish);
#endif