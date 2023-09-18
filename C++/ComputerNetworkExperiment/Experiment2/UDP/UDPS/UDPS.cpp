#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <unordered_map>

#define SERV_IP INADDR_ANY // 监听所有可用网络接口
#define SERV_PORT 8888
const int BUF_SIZE = 1024;

// 创建服务器套接字并监听客户端连接
int ServConnect(int &serv_fd, int &clie_fd)
{
    sockaddr_in serv_addr;

    // 创建Socket
    serv_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (serv_fd == -1)
    {
        std::cerr << "Error: Could not create socket." << std::endl;
        return -1;
    }
    // 配置服务器地址
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT); // 设置服务器监听的端口号
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // 绑定Socket到服务器地址
    if (bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        std::cerr << "Error: Could not bind to port." << std::endl;
        return -1;
    }
    // 开始监听客户端连接
    // if (listen(serv_fd, 128) == -1) // 允许同时连接的客户端数量
    // {
    //     std::cerr << "Error: Could not listen on server socket." << std::endl;
    //     return -1;
    // }

    std::cout << "UDP Server is listening on port 8888..." << std::endl;
    return 0;
}

int ServLogin(const int serv_fd, const int clie_fd, char buf[], int buflen, std::unordered_map<std::string, std::string> &userdata)
{
    return 1;
}

// 提供服务，将客户端发来的消息转换为大写字母并返回
void Service(const int serv_fd, const int clie_fd, char buf[], int buflen)
{
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int n, new_message = 1;
    while (true)
    {
        // 接收来自客户端的数据
        n = recvfrom(serv_fd, buf, buflen, 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (n == -1)
        {
            std::cerr << "Error: Could not receive data." << std::endl;
            break;
        }
        if (new_message && strncmp(buf, "EXIT()\n", 7) == 0)
        {
            printf("Finish Service!\n");
            sendto(serv_fd, "\0", 1, 0, (struct sockaddr *)&clientAddr, clientAddrLen);
            memset(buf, 0, buflen);
            return;
        }
        if (n == BUF_SIZE)
            new_message = 0;
        else
            new_message = 1;
        // 处理接收到的数据
        buf[n] = '\0';
        std::cout << "Received from client: " << buf << std::endl;

        // 发送响应给客户端
        for (int i = 0; i < n; i++)
            buf[i] = toupper(buf[i]); // 将读取的数据转换为大写字母
        sendto(serv_fd, buf, strlen(buf), 0, (struct sockaddr *)&clientAddr, clientAddrLen);
    }
    return;
}

int main()
{
    int serv_fd = 0, clie_fd = 0;

    char buf[BUF_SIZE];

    ServConnect(serv_fd, clie_fd);

    Service(serv_fd, clie_fd, buf, sizeof(buf));

    // 关闭Socket
    close(serv_fd);

    return 0;
}
