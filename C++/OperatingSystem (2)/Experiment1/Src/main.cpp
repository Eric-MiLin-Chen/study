#include "PCB.hpp"

using namespace std;

void PerformanceCompare(vector<PCB> &processes, bool display = false);

void PerformanceCompare(vector<PCB> &processes, bool display)
{
    // Metrics for priority scheduling
    int totalTurnaroundPriority = 0;
    int totalWaitingPriority = 0;
    int n = processes.size();

    if (display)
        cout << "Priority Scheduling:\n";
    PriorityScheduling(processes, display);

    for (const auto &process : processes)
    {
        totalTurnaroundPriority += process.turnaroundTime;
        totalWaitingPriority += process.waitingTime;
    }

    // Metrics for round-robin scheduling
    int totalTurnaroundRoundRobin = 0;
    int totalWaitingRoundRobin = 0;

    // Reset processes for round-robin scheduling
    for (auto &process : processes)
    {
        process.cpuTime = 0;
        process.state = "W";
        process.waitingTime = 0;
        process.turnaroundTime = 0;
    }

    if (display)
        cout << "\nRound Robin Scheduling:\n";
    RoundRobinScheduling(processes, display);

    for (const auto &process : processes)
    {
        totalTurnaroundRoundRobin += process.turnaroundTime;
        totalWaitingRoundRobin += process.waitingTime;
    }

    // Metrics for HRRN scheduling
    int totalTurnaroundHRRN = 0;
    int totalWaitingHRRN = 0;

    // Reset processes for HRRN scheduling
    for (auto &process : processes)
    {
        process.cpuTime = 0;
        process.state = "W";
        process.waitingTime = 0;
        process.turnaroundTime = 0;
    }

    if (display)
        cout << "\nHRRN Scheduling:\n";
    HRRNScheduling(processes, display);

    for (const auto &process : processes)
    {
        totalTurnaroundHRRN += process.turnaroundTime;
        totalWaitingHRRN += process.waitingTime;
    }

    // Display performance metrics
    cout << "\nPerformance Metrics:\n";
    cout << "Priority Scheduling - Average Turnaround Time: " << static_cast<double>(totalTurnaroundPriority) / n << endl;
    cout << "Priority Scheduling - Average Waiting Time: " << static_cast<double>(totalWaitingPriority) / n << endl;

    cout << "Round Robin Scheduling - Average Turnaround Time: " << static_cast<double>(totalTurnaroundRoundRobin) / n << endl;
    cout << "Round Robin Scheduling - Average Waiting Time: " << static_cast<double>(totalWaitingRoundRobin) / n << endl;

    cout << "HRRN Scheduling - Average Turnaround Time: " << static_cast<double>(totalTurnaroundHRRN) / n << endl;
    cout << "HRRN Scheduling - Average Waiting Time: " << static_cast<double>(totalWaitingHRRN) / n << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<PCB> processes;
    InitializeProcesses(processes, n);

    cout << "Enter the scheduling algorithm (PF/RR/HRRN/(0 to compare all)): ";
    string algorithm;
    cin >> algorithm;

    if (algorithm == "PF" || algorithm == "pf")
        PriorityScheduling(processes, true);
    else if (algorithm == "RR" || algorithm == "rr")
        RoundRobinScheduling(processes, true);
    else if (algorithm == "HRRN" || algorithm == "hrrn")
        HRRNScheduling(processes, true);
    else if (algorithm == "0")
    {
        string display;
        cout << "Show progress (T/F): ";
        cin >> display;
        PerformanceCompare(processes, (display == "T" || display == "t" ? true : false));
    }
    else
        cout << "Invalid algorithm entered.\n";

    cout << "System Finished.\n";

    return 0;
}
