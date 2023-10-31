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
    while (true)
    { // 接收客户程序的消息
        msgrcv(msgid, &msg, sizeof(msg.client_pid), 1, 0);

        // 发送自己的pid和ppid给客户程序
        if (msg.mtype == 1)
        {
            msg.mtype = 2;
            msg.client_pid = getpid();
            msgsnd(msgid, &msg, sizeof(msg.client_pid), 0);

            printf("Service process: Received client's pid %d\n", msg.client_pid);
            printf("Service process: Sending my pid %d and ppid %d\n", getpid(), getppid());
        }
        else
            printf("Service process: Ignored invalid message of type %ld\n", msg.mtype);
    }
    // 删除消息队列
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
