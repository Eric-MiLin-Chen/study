#include "PCB.hpp"

using namespace std;

// Function to initialize processes with random values
void InitializeProcesses(vector<PCB> &processes, int n)
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
void DisplayProcesses(const vector<PCB> &processes)
{
    cout << "ID\tPriority\tCPU Time\tAll Time\tState\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes)
    {
        cout << process.id << "\t" << process.priority << "\t\t"
             << process.cpuTime << "\t\t" << process.allTime << "\t\t"
             << process.state << "\t\t" << process.waitingTime << "\t\t"
             << process.turnaroundTime << endl;
    }
    cout << endl;
}

// Priority Scheduling Algorithm
void PriorityScheduling(vector<PCB> &processes, bool display)
{
    sort(processes.begin(), processes.end(), [](const PCB &a, const PCB &b)
         {
             return a.priority > b.priority; // Sort by priority (higher first)
         });

    int currentTime = 0;
    int waitingProcesses = processes.size();

    for (auto &currentprocess : processes)
    {
        while (true)
        {
            currentprocess.cpuTime++;
            currentTime++;

            for (auto &process : processes)
            {
                if (process.state == "F")
                    continue;
                process.waitingTime++;
            }
            currentprocess.waitingTime--;

            if (currentprocess.cpuTime >= currentprocess.allTime)
            {
                currentprocess.turnaroundTime = currentTime;
                currentprocess.state = "F";
                waitingProcesses--;
            }
            if (display)
            {
                cout << "Running Process " << currentprocess.id << endl;
                DisplayProcesses(processes);
            }
            if (currentprocess.cpuTime >= currentprocess.allTime)
                break;
        }
    }
}

// Round Robin Scheduling Algorithm
void RoundRobinScheduling(vector<PCB> &processes, bool display, int timeSlice)
{
    int currentTime = 0;
    int waitingProcess = processes.size();

    while (waitingProcess)
    {
        for (auto &currentprocess : processes)
        {
            if (currentprocess.state == "F")
                continue;

            currentprocess.waitingTime -= timeSlice;
            currentprocess.cpuTime += timeSlice;
            currentTime += timeSlice;

            for (auto &process : processes)
            {
                if (process.state == "F")
                    continue;
                process.waitingTime += timeSlice;
            }

            if (currentprocess.cpuTime >= currentprocess.allTime)
            {
                currentprocess.turnaroundTime = currentTime;
                currentprocess.state = "F";
                waitingProcess--;
            }

            if (display)
            {
                cout << "Running Process " << currentprocess.id << endl;
                DisplayProcesses(processes);
            }
        }
    }
}

// HRRN Scheduling Algorithm
void HRRNScheduling(vector<PCB> &processes, bool display)
{
    int currentTime = 0;
    int waitingProcesses = processes.size();

    while (waitingProcesses)
    {
        // Calculate the response ratio for each process
        for (auto &process : processes)
        {
            double responseRatio = (currentTime - process.cpuTime + process.allTime) / static_cast<double>(process.allTime);
            process.priority = responseRatio;
            if (process.state == "F")
                continue;
            process.waitingTime++;
        }

        // Sort processes based on response ratio (higher first)
        sort(processes.begin(), processes.begin() + waitingProcesses, [](const PCB &a, const PCB &b)
             { return a.priority > b.priority; });

        // Run the process with the highest response ratio
        auto &currentprocess = processes.front();

        currentprocess.waitingTime--;
        currentprocess.cpuTime++;
        currentTime++;

        if (currentprocess.cpuTime >= currentprocess.allTime)
        {
            currentprocess.turnaroundTime = currentTime - currentprocess.waitingTime;
            currentprocess.state = "F"; // Set process state to finish
            rotate(processes.begin(), processes.begin() + 1, processes.end());
            waitingProcesses--;
        }

        if (display)
        {
            cout << "Running Process " << currentprocess.id << endl;
            DisplayProcesses(processes);
        }
    }
}