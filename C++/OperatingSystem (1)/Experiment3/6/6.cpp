/*程序建立一个管道fd*/
/*父进程创建两个子进程P1、P2 */
/*子进程P1、P2 分别向管道写入信息*/
/*父进程等待子进程结束，并读出管道中的信息*/
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int read_nums, pid, ppid, p1, p2, fd[2];
    char buf[50], s[50];
    int res = pipe(fd);         /*建立一个管道fd*/
    while ((p1 = fork()) == -1) /*创建子进程1*/
        ;
    if (p1 == 0) /*子进程1执行*/
    {
        res = lockf(fd[1], 1, 0); /*管道写入端加锁*/
        sprintf(buf, "Child process P1 is sending messages! \n");
        printf("Child process P1! \n");
        res = write(fd[1], buf, 50); /*信息写入管道*/
        res = lockf(fd[1], 0, 0);    /*管道写入端解锁*/
        sleep(5);
        pid = getpid();
        ppid = getppid();
        printf("P1 %d is wakeup. My parent process ID is %d.\n", pid, ppid);
        exit(0);
    }
    else
    {
        while ((p2 = fork()) == -1) /*创建子进程2*/
            ;
        if (p2 == 0) /*子进程2执行*/
        {
            res = lockf(fd[1], 1, 0); /*管道写入端加锁*/
            sprintf(buf, "Child process P2 is sending messages! \n");
            printf("Child process P2! \n");
            res = write(fd[1], buf, 50); /*信息写入管道*/
            res = lockf(fd[1], 0, 0);    /*管道写入端解锁*/
            sleep(5);
            pid = getpid();
            ppid = getppid();
            printf("P2 %d is wakeup. My parent process ID is %d.\n", pid, ppid);
            exit(0);
        }
        else
        {
            pid = getpid();
            wait(0); /* 等待被唤醒*/
            if (read_nums = read(fd[0], s, 50) == -1)
                printf("Can't read pipe. \n");
            else
                printf("Parent %d: %s \n", pid, s);
            wait(0); /* 等待被唤醒*/
            if (read_nums = read(fd[0], s, 50) == -1)
                printf("Can't read pipe. \n");
            else
                printf("Parent %d: %s \n", pid, s);
            exit(0);
        }
    }
}