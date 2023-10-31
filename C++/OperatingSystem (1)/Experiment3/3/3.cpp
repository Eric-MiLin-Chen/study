#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    std::cout << "进程标识(PID): " << getpid() << std::endl
              << "父进程标识(PPID): " << getppid() << std::endl;

    for (int i = 0; i < 3; i++)
    {
        pid_t child_pid = fork();

        if (child_pid == -1)
        {
            std::cerr << "无法创建子进程" << std::endl;
            return 1;
        }

        if (child_pid == 0)
        {
            // 子进程执行的代码
            std::cout << i << ": PID=" << getpid() << " PPID=" << getppid() << std::endl;
            // 子进程执行一些任务
            sleep(2); // 等待2秒
            return 0; // 子进程正常退出
        }
    }

    // 父进程等待所有子进程结束
    int status;
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
        {
            int child_exit_status = WEXITSTATUS(status);
            std::cout << "子进程 " << WTERMSIG(status) << " 正常退出，退出状态码: " << child_exit_status << std::endl;
        }
        else if (WIFSIGNALED(status))
        {
            std::cout << "子进程 " << WTERMSIG(status) << " 被信号终止" << std::endl;
        }
    }

    return 0;
}
