#include "PCB.hpp"

using namespace std;

// 函数声明，用于比较不同调度算法的性能
void PerformanceCompare(vector<PCB> &processes, bool display = false);

// 比较不同调度算法的性能
void PerformanceCompare(vector<PCB> &processes, bool display)
{
    // 优先级调度的性能指标
    int totalTurnaroundPriority = 0;
    int totalWaitingPriority = 0;
    int n = processes.size();

    if (display)
        cout << "Priority Scheduling:\n";
    PriorityScheduling(processes, display);

    // 计算优先级调度的平均周转时间和平均等待时间
    for (const auto &process : processes)
    {
        totalTurnaroundPriority += process.turnaroundTime;
        totalWaitingPriority += process.waitingTime;
    }

    // 循环轮转调度的性能指标
    int totalTurnaroundRoundRobin = 0;
    int totalWaitingRoundRobin = 0;

    // 为循环轮转调度重置进程
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

    // 计算循环轮转调度的平均周转时间和平均等待时间
    for (const auto &process : processes)
    {
        totalTurnaroundRoundRobin += process.turnaroundTime;
        totalWaitingRoundRobin += process.waitingTime;
    }

    // HRRN调度的性能指标
    int totalTurnaroundHRRN = 0;
    int totalWaitingHRRN = 0;

    // 为HRRN调度重置进程
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

    // 计算HRRN调度的平均周转时间和平均等待时间
    for (const auto &process : processes)
    {
        totalTurnaroundHRRN += process.turnaroundTime;
        totalWaitingHRRN += process.waitingTime;
    }

    // 显示性能指标
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

    // 输入要使用的调度算法
    cout << "Enter the scheduling algorithm (PF/RR/HRRN/(0 to compare all)): ";
    string algorithm;
    cin >> algorithm;

    // 根据用户输入选择调度算法
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
