/*创建子进程，子进程启动其它程序*/
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int child_pid1, child_pid2, child_pid3;
    int pid, status;
    setbuf(stdout, NULL);
    child_pid1 = fork(); /*创建子进程1*/
    if (child_pid1 == 0)
    {
        execlp("echo", "echo", "child process 1", (char *)0);
        /*子进程1启动其它程序*/
        perror("exec1 error.\n ");
        exit(1);
    }
    child_pid2 = fork(); /*创建子进程2*/
    if (child_pid2 == 0)
    {
        execlp("date", "date", (char *)0); /*子进程2启动其它程序*/
        perror("exec2 error.\n ");
        exit(2);
    }
    child_pid3 = fork(); /*创建子进程3*/
    if (child_pid3 == 0)
    {
        execlp("ls", "ls", (char *)0); /*子进程3启动其它程序*/
        perror("exec3 error.\n ");
        exit(3);
    }
    puts("Parent process is waiting for chile process return!");
    while ((pid = wait(&status)) != -1) /*等待子进程结束*/
    {
        if (child_pid1 == pid) /*若子进程1结束*/
            printf("child process 1 terminated with status %d\n", (status >> 8));
        else
        {
            if (child_pid2 == pid) /*若子进程2结束*/
                printf("child process 2 terminated with status %d\n", (status >> 8));
            else
            {
                if (child_pid3 == pid) /*若子进程3 结束*/
                    printf("child process 3 terminated with status %d\n", (status >> 8));
            }
        }
    }
    puts("All child processes terminated.");
    puts("Parent process terminated.");
    exit(0);
}
