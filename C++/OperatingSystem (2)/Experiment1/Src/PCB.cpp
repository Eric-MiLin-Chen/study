#include "PCB.hpp"

using namespace std;

// Function to initialize processes with random values
void initializeProcesses(vector<PCB> &processes, int n)
{
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        PCB process;
        process.id = i + 1;
        process.priority = rand() % 10; // Random priority for simplicity
        process.cpuTime = 0;
        process.allTime = 3 + rand() % 5; // Random required time slices
        process.state = "W";              // Initial state is waiting
        process.waitingTime = 0;
        process.turnaroundTime = 0;
        processes.push_back(process);
    }
}

// Function to display the current state of processes
void displayProcesses(const vector<PCB> &processes)
{
    cout << "ID\tPriority\tCPU Time\tAll Time\tState\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes)
    {
        cout << process.id << "\t" << process.priority << "\t\t"
             << process.cpuTime << "\t\t" << process.allTime << "\t\t"
             << process.state << "\t\t" << process.waitingTime << "\t\t"
             << process.turnaroundTime << endl;
    }
}

// Priority Scheduling Algorithm
void priorityScheduling(vector<PCB> &processes, bool display)
{
    sort(processes.begin(), processes.end(), [](const PCB &a, const PCB &b)
         {
             return a.priority > b.priority; // Sort by priority (higher first)
         });

    int currentTime = 0;

    while (!processes.empty())
    {
        auto &process = processes.front();
        process.waitingTime = currentTime;
        while (process.cpuTime < process.allTime)
        {
            if (display)
                cout << "Running Process " << process.id << endl;
            process.cpuTime++;
            currentTime++;
            if (display)
                displayProcesses(processes);
        }
        process.state = "F"; // Set process state to finish
        processes.erase(remove_if(processes.begin(), processes.end(),
                                  [](const PCB &p)
                                  { return p.state == "F"; }),
                        processes.end());
        if (display)
            displayProcesses(processes);
    }
}

// Round Robin Scheduling Algorithm
void roundRobinScheduling(vector<PCB> &processes, int timeSlice, bool display)
{
    while (!processes.empty())
    {
        int currentTime = 0;

        for (auto &process : processes)
        {
            process.waitingTime = currentTime;
            currentTime += timeSlice;

            if (display)
                cout << "Running Process " << process.id << endl;
            process.cpuTime += timeSlice;

            if (process.cpuTime >= process.allTime)
            {
                process.turnaroundTime = currentTime - process.waitingTime;
                process.state = "F"; // Set process state to finish
                processes.erase(remove_if(processes.begin(), processes.end(),
                                          [](const PCB &p)
                                          { return p.state == "F"; }),
                                processes.end());
            }

            if (display)
                displayProcesses(processes);
        }
    }
}

// HRRN Scheduling Algorithm
void hrrnScheduling(vector<PCB> &processes, bool display)
{
    int currentTime = 0;

    while (!processes.empty())
    {
        // Calculate the response ratio for each process
        for (auto &process : processes)
        {
            double responseRatio = (currentTime - process.cpuTime + process.allTime) / static_cast<double>(process.allTime);
            process.priority = responseRatio;
        }

        // Sort processes based on response ratio (higher first)
        sort(processes.begin(), processes.end(), [](const PCB &a, const PCB &b)
             { return a.priority > b.priority; });

        // Run the process with the highest response ratio
        auto &process = processes.front();
        if (display)
            cout << "Running Process " << process.id << endl;
        process.cpuTime++;

        if (process.cpuTime >= process.allTime)
        {
            process.turnaroundTime = currentTime - process.waitingTime;
            process.state = "F"; // Set process state to finish
            processes.erase(remove_if(processes.begin(), processes.end(),
                                      [](const PCB &p)
                                      { return p.state == "F"; }),
                            processes.end());
        }

        for (auto &process : processes)
        {
            if (process.state == "W")
                process.waitingTime++;
        }

        currentTime++;
        if (display)
            displayProcesses(processes);
    }
}

// Banker's Algorithm for Resource Allocation
bool isSafeState(const vector<vector<int>> &max, const vector<vector<int>> &allocation,
                 const vector<int> &available, vector<int> &work, vector<bool> &finish)
{
    int numProcesses = max.size();
    int numResources = max[0].size();

    for (int i = 0; i < numProcesses; ++i)
    {
        if (!finish[i])
        {
            bool canAllocate = true;
            for (int j = 0; j < numResources; ++j)
            {
                if (max[i][j] - allocation[i][j] > work[j])
                {
                    canAllocate = false;
                    break;
                }
            }

            if (canAllocate)
            {
                for (int j = 0; j < numResources; ++j)
                {
                    work[j] += allocation[i][j];
                }
                finish[i] = true;
                return true;
            }
        }
    }

    return false;
}

// Banker's Algorithm Implementation
// void bankersAlgorithm(const vector<vector<int>> &max, const vector<vector<int>> &allocation, const vector<int> &available)
// {
//     int numProcesses = max.size();
//     int numResources = max[0].size();

//     vector<int> work = available;
//     vector<bool> finish(numProcesses, false);

//     for (int i = 0; i < numProcesses; ++i)
//     {
//         if (!finish[i])
//         {
//             if (isSafeState(max, allocation, available, work, finish))
//             {
//                 cout << "Running Process " << i + 1 << endl;
//                 finish[i] = true;
//                 displayProcesses(processes);
//             }
//             else
//             {
//                 cout << "Unsafe state. Cannot proceed with process " << i + 1 << endl;
//                 break;
//             }
//         }
//     }
// }