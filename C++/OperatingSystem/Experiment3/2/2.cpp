#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int CreateChildProcess()
{
    pid_t child_pid = fork(); // 创建子进程

    if (child_pid == -1)
    {
        std::cerr << "无法创建子进程" << std::endl;
        exit(-1);
    }

    if (child_pid == 0)
    {
        // 子进程执行的代码段
        std::cout << "子进程，PID: " << getpid() << std::endl;
        std::cout << "子进程执行的代码..." << std::endl;
        exit(1); // 子进程返回1表示成功执行
    }
    else
    {
        // 父进程执行的代码段
        std::cout << "这是父进程，PID: " << getpid() << std::endl;

        // 等待子进程结束并获取其返回值
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status))
        {
            int child_exit_status = WEXITSTATUS(status);
            std::cout << "子进程返回值为: " << child_exit_status << std::endl;

            // if (child_exit_status == 0)
            // {
            //     std::cout << "父进程执行其他操作..." << std::endl;
            //     // 在这里可以添加父进程需要执行的其他操作
            // }
            // else
            // {
            //     std::cout << "子进程执行失败，父进程执行其他操作..." << std::endl;
            //     // 在这里可以添加父进程需要执行的其他操作
            // }
        }
        exit(1);
    }
}

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
        CreateChildProcess();
    }
    else
    {
        std::cout << "操作结束。" << std::endl;
    }

    return 0;
}
