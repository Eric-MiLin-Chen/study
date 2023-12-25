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
        process.priority = rand() % 10; // 为简单起见，随机生成优先级
        process.cpuTime = 0;
        process.allTime = 3 + rand() % 5; // 随机生成所需的时间片
        process.state = "W";              // 初始状态为等待
        process.waitingTime = 0;
        process.turnaroundTime = 0;
        process.submissionTime = rand() % 15;
        printf("CLAIM OF PROCESS %d IS:", i + 1);
        for (int j = 0; j < RESOURCE_TYPES; j++)
            cin >> process.claim[i];
        processes.push_back(process);
    }
}

// Function to display the current state of processes
void DisplayCPUUsage(const vector<PCB> &processes)
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

// Function to display the current state of processes
void DisplayResourceUsage(const vector<PCB> &processes)
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
             return a.priority > b.priority; // 按优先级排序（高优先级优先）
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
                DisplayCPUUsage(processes);
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
                DisplayCPUUsage(processes);
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
        // 计算每个进程的响应比
        for (auto &process : processes)
        {
            double responseRatio = (currentTime - process.cpuTime + process.allTime) / static_cast<double>(process.allTime);
            process.priority = responseRatio;
            if (process.state == "F")
                continue;
            process.waitingTime++;
        }

        // 根据响应比排序进程（高响应比优先）
        sort(processes.begin(), processes.begin() + waitingProcesses, [](const PCB &a, const PCB &b)
             { return a.priority > b.priority; });

        // 运行响应比最高的进程
        auto &currentprocess = processes.front();

        currentprocess.waitingTime--;
        currentprocess.cpuTime++;
        currentTime++;

        if (currentprocess.cpuTime >= currentprocess.allTime)
        {
            currentprocess.turnaroundTime = currentTime - currentprocess.waitingTime;
            currentprocess.state = "F"; // 将进程状态设置为完成
            rotate(processes.begin(), processes.begin() + 1, processes.end());
            waitingProcesses--;
        }

        if (display)
        {
            cout << "Running Process " << currentprocess.id << endl;
            DisplayCPUUsage(processes);
        }
    }
}
