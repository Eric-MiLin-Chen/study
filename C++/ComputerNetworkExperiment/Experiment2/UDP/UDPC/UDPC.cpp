#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8888
const int BUF_SIZE = 1024;

int ClieConnect(sockaddr_in &serv_addr, int &clie_fd)
{
    // 创建Socket
    clie_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (clie_fd == -1)
    {
        std::cerr << "Error: Could not create socket." << std::endl;
        return -1;
    }

    // 配置服务器地址
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);          // 服务器的端口号
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP); // 服务器的IP地址
    return 1;
}

int ClieLogin(const int clie_fd, char buf[], int buflen, const int login_counter = 0)
{
    return 1;
}

void Service(sockaddr_in &serv_addr, int &clie_fd, char buf[], int buflen)
{
    socklen_t serverAddrLen = sizeof(serv_addr);
    while (true)
    {
        fgets(buf, buflen, stdin); // 参数1：目的缓冲区指针，参数2：缓冲区大小，参数3：源数据流；stdin：标准输入
        sendto(clie_fd, buf, strlen(buf), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        int n = recvfrom(clie_fd, buf, buflen, 0, (struct sockaddr *)&serv_addr, &serverAddrLen); // 写完之后发给服务端了，服务端会响应回来，现在该读了
        if (buf[0] != '\n' && n == 1)
        {
            printf("Log Out!\n");
            return;
        }
        write(STDOUT_FILENO, buf, n); // 把读到的服务器的响应写到屏幕
    }
    return;
}

int main()
{
    int serv_fd, clie_fd;
    char buf[1024];
    sockaddr_in serv_addr;

    ClieConnect(serv_addr, clie_fd);
    ClieLogin(clie_fd, buf, BUF_SIZE);
    Service(serv_addr, clie_fd, buf, BUF_SIZE);

    // 关闭Socket
    close(clie_fd);

    return 0;
}
