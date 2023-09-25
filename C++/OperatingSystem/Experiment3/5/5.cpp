/*创建子进程的实验。子进程继承父进程的资源，修改了公共变量globa和私有变量vari。观察变化情况。*/
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int globa = 4;

int main()
{
    pid_t pid;
    int vari = 5;
    printf("before fork.\n");
    if ((pid = fork()) < 0) /*创建失败处理*/
    {
        printf("fork error.\n");
        exit(0);
    }
    else
    {
        if (pid == 0) /*子进程执行*/
        {
            globa++;
            vari--;
            printf("Child %d changed the vari and globa.\n", getpid());
        }
        else /*父进程执行*/
            printf("Parent %d did not changed the vari and globa.\n", getpid());
        printf("pid=%d, globa=%d, vari=%d\n", getpid(), globa, vari); /*都执行*/
        exit(0);
    }
}