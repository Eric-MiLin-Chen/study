#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    // 获取进程标识（PID）
    pid_t pid = getpid();
    std::cout << "进程标识 (PID): " << pid << std::endl;

    // 获取父进程标识（PPID）
    pid_t ppid = getppid();
    std::cout << "父进程标识 (PPID): " << ppid << std::endl;

    // 获取用户标识（UID）
    uid_t uid = getuid();
    std::cout << "用户标识 (UID): " << uid << std::endl;

    // 获取组标识（GID）
    gid_t gid = getgid();
    std::cout << "组标识 (GID): " << gid << std::endl;

    // 等待5秒
    std::cout << "等待5秒..." << std::endl;
    sleep(5);

    // 执行另一个程序，这里用系统调用system执行一个示例程序，你可以替换为你需要执行的程序
    std::cout << "执行另一个程序..." << std::endl;
    int res = system("ls"); // 示例：执行 "ls" 命令

    // 询问用户是否继续
    char choice;
    std::cout << "是否继续操作？(Y/N): ";
    std::cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        std::cout << "继续操作..." << std::endl;
    }
    else
    {
        std::cout << "操作结束。" << std::endl;
    }

    return 0;
}
