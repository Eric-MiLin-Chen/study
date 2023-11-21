#include "PCB.hpp"

using namespace std;

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<PCB> processes;
    initializeProcesses(processes, n);

    // Metrics for priority scheduling
    int totalTurnaroundPriority = 0;
    int totalWaitingPriority = 0;

    cout << "Enter the scheduling algorithm (priority/roundrobin/hrrn/bankers): ";
    string algorithm;
    cin >> algorithm;

    if (algorithm == "priority")
    {
        priorityScheduling(processes, true);
    }
    else if (algorithm == "roundrobin")
    {
        roundRobinScheduling(processes, true);
    }
    else if (algorithm == "hrrn")
    {
        hrrnScheduling(processes, true);
    }
    else if (algorithm == "bankers")
    {
        // Assuming you have matrices for max and allocation and a vector for available
        // bankersAlgorithm(max, allocation, available);
    }
    else
    {
        cout << "Invalid algorithm entered.\n";
    }

    cout << "System Finished.\n";

    return 0;
}
