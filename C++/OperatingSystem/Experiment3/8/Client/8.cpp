#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 12345

struct message
{
    long mtype;
    pid_t client_pid;
};

int main()
{
    int msgid;
    struct message msg;

    // 创建或获取消息队列
    msgid = msgget(MSGKEY, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    // 获取自己的进程ID
    pid_t my_pid = getpid();

    // 发送自己的进程ID给服务者
    msg.mtype = 1;
    msg.client_pid = my_pid;
    msgsnd(msgid, &msg, sizeof(msg.client_pid), 0);

    // 接收服务者的回复
    msgrcv(msgid, &msg, sizeof(msg.client_pid), 2, 0);
    if (msg.mtype == 2)
        printf("Client process: Received service process's pid %d and ppid %d\n", msg.client_pid, getppid());
    else
        printf("Client process: Ignored invalid message of type %ld\n", msg.mtype);

    return 0;
}
