#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc, char *argv[])
{
    unsigned short port = 8000;    // 服务器的端口号
    char *server_ip = "127.0.0.1"; // 服务器ip地址

    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 创建通信端点：套接字
    if (sockfd < 0)
    {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr)); // 初始化服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    int err_log = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // 主动连接服务器
    if (err_log != 0)
    {
        perror("connect");
        close(sockfd);
        exit(-1);
    }

    system("netstat -an | grep 8000"); // 查看连接状态

    sleep(10); // 延时10s

    return 0;
}
