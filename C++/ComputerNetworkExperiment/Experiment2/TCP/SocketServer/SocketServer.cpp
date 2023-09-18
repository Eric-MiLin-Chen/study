#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <thread>

#define SERV_IP INADDR_ANY // 监听所有可用网络接口
#define SERV_PORT 8888
const int NameAndPasswdSize = 20;
const int BUF_SIZE = 1024;
const int LOGIN_EXIT = 4;
std::unordered_map<std::string, std::string> userdata;

// 从文件加载用户名和密码到unordered_map
int LoadFile(std::string usernamedir, std::string passwddir, std::unordered_map<std::string, std::string> &data)
{
    std::ifstream usernamefile(usernamedir.c_str()), passwdfile(passwddir.c_str()); // 打开输入文件
    if (!usernamefile && !passwdfile)
    {
        std::cerr << "无法打开输入文件" << std::endl;
        return 0;
    }
    else
    {
        std::string username, passwd;
        while (getline(usernamefile, username), getline(passwdfile, passwd))
            data.emplace(username, passwd); // 将用户名和密码插入unordered_map
        usernamefile.close();
        passwdfile.close();
    }
    return 1;
}

// 创建服务器套接字并监听客户端连接
int ServConnect(int &serv_fd, int &clie_fd)
{
    struct sockaddr_in serv_addr, clie_addr; // 服务器地址结构和客户端地址结构
    socklen_t clie_addr_len;                 // 客户端地址结构的长度
    char clie_ip_buf[BUF_SIZE];              // 数据缓冲区和用于存储客户端IP地址的缓冲区

    // 创建服务器套接字
    if (!serv_fd)
    {
        serv_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (serv_fd == -1)
        {
            std::cerr << "Error creating server socket." << std::endl;
            return -1;
        }
        // 初始化服务器地址结构
        bzero(&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(SERV_PORT);      // 设置监听端口号
        serv_addr.sin_addr.s_addr = htonl(SERV_IP); // 监听所有可用网络接口

        // 绑定服务器套接字到服务器地址
        if (bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        {
            std::cerr << "Error binding server socket." << std::endl;
            return -1;
        }

        // 开始监听客户端连接
        if (listen(serv_fd, 128) == -1) // 允许同时连接的客户端数量
        {
            std::cerr << "Error listening on server socket." << std::endl;
            return -1;
        }
    }

    // 接受客户端连接请求
    clie_addr_len = sizeof(clie_addr);
    clie_fd = accept(serv_fd, (struct sockaddr *)&clie_addr, &clie_addr_len);
    if (clie_fd == -1)
    {
        std::cerr << "Error accepting client connection." << std::endl;
        return -1;
    }
    else // 打印客户端的IP地址和端口号
    {
        printf("client IP: %s,  client port: %d\n",
               inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr,
                         clie_ip_buf, sizeof(clie_ip_buf)),
               ntohs(clie_addr.sin_port));
        return 1;
    }
}

// 服务器登录功能，验证用户名和密码
int ServLogin(const int serv_fd, const int clie_fd, char buf[], int buflen, std::unordered_map<std::string, std::string> &userdata, const int login_counter = 0)
{
    int username_flag = recv(clie_fd, buf, buflen, 0); // 从客户端套接字读取数据
    for (int i = 0; i <= username_flag; i++)
        if (buf[i] == '\n')
            buf[i] = '\0';
    std::string username = buf;
    username_flag = (userdata.count(username) > 0) && (username_flag <= NameAndPasswdSize) && (username != "");
    printf("Username: %s\n", buf);

    int password_flag = recv(clie_fd, buf, buflen, 0); // 从客户端套接字读取数据
    for (int i = 0; i <= password_flag; i++)
        if (buf[i] == '\n')
            buf[i] = '\0';
    std::string password = buf;
    password_flag = (password == userdata[username]) && (password_flag <= NameAndPasswdSize) && (password != "");
    printf("Password: %s\n", buf);

    if (username_flag && password_flag)
    {
        printf("Judgment: True\n");
        send(clie_fd, "T", 2, 0);
        return 1;
    }
    else if (login_counter + 1 == LOGIN_EXIT)
    {
        send(clie_fd, "F", 2, 0);
        printf("LOGIN Failed!\nExiting\n\n");
        return -1;
    }
    else
    {
        printf("Judgment: False\nRelogining...\n\n");
        buf[0] = '0' + LOGIN_EXIT;
        buf[1] = '\0';
        send(clie_fd, buf, 2, 0);
        return ServLogin(serv_fd, clie_fd, buf, buflen, userdata, login_counter + 1);
    }
    return -1;
}

// 提供服务，将客户端发来的消息转换为大写字母并返回
void Service(const int serv_fd, const int clie_fd, char buf[], int buflen)
{
    int n, new_message = 1;
    while (true)
    {
        n = recv(clie_fd, buf, buflen, 0); // 从客户端套接字读取数据
        if (new_message && strncmp(buf, "EXIT()\n", 7) == 0)
        {
            printf("Finish Service!\n");
            send(clie_fd, "\0", 1, 0);
            memset(buf, 0, buflen);
            return;
        }
        if (n == BUF_SIZE)
            new_message = 0;
        else
            new_message = 1;
        for (int i = 0; i < n; i++)
            buf[i] = toupper(buf[i]); // 将读取的数据转换为大写字母
        send(clie_fd, buf, n, 0);     // 将转换后的数据写回客户端
    }
    return;
}

void HandleClient(int serv_fd, int clie_fd)
{
    char buf[BUF_SIZE];
    if (ServLogin(serv_fd, clie_fd, buf, sizeof(buf), userdata) != -1)
        Service(serv_fd, clie_fd, buf, sizeof(buf));
    close(clie_fd);
}

int main()
{
    int serv_fd = 0, clie_fd = 0; // 服务器套接字和客户端套接字
    std::string usernamedir = "./username.txt", passwddir = "./passwd.txt";
    std::vector<std::thread> threads;

    LoadFile(usernamedir, passwddir, userdata);

    printf("TCP Server started.\n");
    while (true)
    {
        if (ServConnect(serv_fd, clie_fd) != -1)
            threads.emplace_back(HandleClient, serv_fd, clie_fd);
    }
    close(serv_fd);
    return 0;
}
