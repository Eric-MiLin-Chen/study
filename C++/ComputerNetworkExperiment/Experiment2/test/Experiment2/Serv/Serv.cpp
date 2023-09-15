#include <iostream>
#include <cstring>
#include <thread>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// 函数用于处理客户端连接
void HandleClient(int client_socket)
{
    char buffer[1024];
    int bytes_received;

    while (true)
    {
        // 接收客户端消息
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            break;
        }

        // 将接收到的消息转换为大写
        for (int i = 0; i < bytes_received; ++i)
        {
            buffer[i] = std::toupper(buffer[i]);
        }

        // 发送大写消息给客户端
        send(client_socket, buffer, bytes_received, 0);

        // 检查是否接收到退出命令
        if (strncmp(buffer, "exit", 4) == 0)
        {
            break;
        }
    }

    // 关闭客户端连接
    close(client_socket);
}

int main()
{
    int server_socket, client_socket;
    sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 创建套接字
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cerr << "Error: Unable to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 绑定套接字
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Error: Unable to bind to port" << std::endl;
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "Error: Unable to listen for connections" << std::endl;
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port 8080..." << std::endl;

    std::vector<std::thread> threads;

    while (true)
    {
        // 接受客户端连接
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1)
        {
            std::cerr << "Error: Unable to accept client connection" << std::endl;
            continue;
        }

        // 创建一个新的子线程来处理客户端连接
        threads.emplace_back(HandleClient, client_socket);
    }

    // 关闭服务器套接字
    close(server_socket);

    return 0;
}
