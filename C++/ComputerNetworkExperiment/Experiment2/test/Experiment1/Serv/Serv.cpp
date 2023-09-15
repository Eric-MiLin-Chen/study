#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char *argv[])
{
    unsigned short port = 8000;

    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 创建通信端点：套接字
    if (sockfd < 0)
    {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int err_log = bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
    if (err_log != 0)
    {
        perror("binding");
        close(sockfd);
        exit(-1);
    }

    err_log = listen(sockfd, 10);
    if (err_log != 0)
    {
        perror("listen");
        close(sockfd);
        exit(-1);
    }

    printf("listen client @port=%d...\n", port);

    sleep(10); // 延时10s

    system("netstat -an | grep 8000"); // 查看连接状态

    return 0;
}
