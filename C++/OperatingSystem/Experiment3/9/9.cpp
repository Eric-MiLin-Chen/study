/* 父进程向子进程发送18 号软中断信号后等待。子进程收到信号，执行指定的程序，再将父进程唤醒。*/
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void func(int signal_number);

int main()
{
    int i, j, k;
    signal(18, func);    /*设置18号信号的处理程序*/
    if (i = fork())      /*创建子进程*/
    {                    /*父进程执行*/
        j = kill(i, 18); /*向子进程发送信号*/
        printf("Parent: signal 18 has been sent to child %d,returned %d.\n", i, j);
        k = wait(0); /*父进程被唤醒*/
        printf("After wait %d,Parent %d: finished.\n", k, getpid());
    }
    else
    { /*子进程执行*/
        sleep(10);
        printf("Child %d: A signal from my parent is recived.\n", getpid());
    } /*子进程结束，向父进程发子进程结束信号*/
}
void func(int signal_number) /*处理程序*/
{
    printf("I am Process %d: It is signal %d processing function.\n", getpid(), signal_number);
}