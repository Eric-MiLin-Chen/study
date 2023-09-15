#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#define SERV_IP INADDR_ANY // 监听所有可用网络接口
#define SERV_PORT 8888
const char username[] = "Eric";
const char password[] = "123456";
const int NameAndPasswdSize = 20;
const int BUF_SIZE = 1024;

int ServConnect(int &serv_fd, int &clie_fd)
{
    struct sockaddr_in serv_addr, clie_addr; // 服务器地址结构和客户端地址结构
    socklen_t clie_addr_len;                 // 客户端地址结构的长度
    char clie_ip_buf[BUF_SIZE];              // 数据缓冲区和用于存储客户端IP地址的缓冲区

    // 创建服务器套接字
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    // std::cout << serv_fd << std::endl;

    // 初始化服务器地址结构
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);      // 设置监听端口号
    serv_addr.sin_addr.s_addr = htonl(SERV_IP); // 监听所有可用网络接口

    // 绑定服务器套接字到服务器地址
    bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // 开始监听客户端连接
    listen(serv_fd, 128); // 允许同时连接的客户端数量

    // 接受客户端连接请求
    clie_addr_len = sizeof(clie_addr);
    clie_fd = accept(serv_fd, (struct sockaddr *)&clie_addr, &clie_addr_len);
    if (clie_fd > 0)
    // 打印客户端的IP地址和端口号
    {
        printf("client IP: %s,  client port: %d\n",
               inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr,
                         clie_ip_buf, sizeof(clie_ip_buf)),
               ntohs(clie_addr.sin_port));
        return 1;
    }
    else
        return 0;
}

int ServLogin(const int serv_fd, const int clie_fd, char buf[], int buflen)
{
    int username_flag = read(clie_fd, buf, buflen); // 从客户端套接字读取数据
    if (username_flag > 0 && buf[username_flag - 1] == '\n')
        buf[username_flag - 1] = '\0';
    username_flag = (strcmp(buf, username) == 0) && (username_flag <= NameAndPasswdSize) && (buf[0] != '\0');
    printf("Username: %s\n", buf);

    int password_flag = read(clie_fd, buf, buflen); // 从客户端套接字读取数据
    if (password_flag > 0 && buf[password_flag - 1] == '\n')
        buf[password_flag - 1] = '\0';
    password_flag = (strcmp(buf, password) == 0) && (password_flag <= NameAndPasswdSize);
    printf("Password: %s\n", buf);

    if (username_flag && password_flag)
    {
        printf("Judgment: True\n");
        write(clie_fd, "T", 2);
        return 1;
    }
    else
    {
        printf("Judgment: False\nRelogining...\n\n");
        write(clie_fd, "F", 2);
        return ServLogin(serv_fd, clie_fd, buf, buflen);
    }
    return 0;
}

void Service(const int serv_fd, const int clie_fd, char buf[], int buflen)
{
    int n, new_message = 1;
    while (true)
    {
        n = read(clie_fd, buf, buflen); // 从客户端套接字读取数据
        if (new_message && strncmp(buf, "EXIT()\n", 7) == 0)
        {
            printf("Finish Service!\n");
            write(clie_fd, "\0", 1);
            return;
        }
        if (n == BUF_SIZE)
            new_message = 0;
        else
            new_message = 1;
        for (int i = 0; i < n; i++)
            buf[i] = toupper(buf[i]); // 将读取的数据转换为大写字母
        write(clie_fd, buf, n);       // 将转换后的数据写回客户端
    }
}

int main()
{
    int serv_fd, clie_fd; // 服务器套接字和客户端套接字
    char buf[BUF_SIZE];

    printf("TCP Server started.\n");
    while (true)
    {
        if (ServConnect(serv_fd, clie_fd))
        {
            if (ServLogin(serv_fd, clie_fd, buf, sizeof(buf)))
                // 不断读取客户端发送的数据，转换为大写字母后回传给客户端
                Service(serv_fd, clie_fd, buf, sizeof(buf));
            // 关闭服务器和客户端套接字
            close(serv_fd);
            close(clie_fd);
        }
    }
    return 0;
}
