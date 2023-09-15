#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int client_socket;
    sockaddr_in server_addr;
    char server_ip[] = "127.0.0.1"; // 服务器IP地址
    int server_port = 8080;         // 服务器端口号

    // 创建套接字
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        std::cerr << "Error: Unable to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    // 连接到服务器
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Error: Unable to connect to server" << std::endl;
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to server at " << server_ip << ":" << server_port << std::endl;
    std::cout << "Type 'exit' to disconnect." << std::endl;

    while (true)
    {
        // 读取用户输入
        std::string message;
        std::cout << "Enter a message: ";
        std::getline(std::cin, message);

        // 发送消息给服务器
        send(client_socket, message.c_str(), message.size(), 0);

        // 检查是否输入了"exit"来关闭连接
        if (message == "exit")
        {
            break;
        }

        // 接收服务器的响应
        char buffer[1024];
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received == -1)
        {
            std::cerr << "Error: Unable to receive data from server" << std::endl;
            break;
        }
        else if (bytes_received == 0)
        {
            std::cout << "Server closed the connection." << std::endl;
            break;
        }
        else
        {
            // 显示服务器响应
            std::cout << "Server response: " << std::string(buffer, bytes_received) << std::endl;
        }
    }

    // 关闭客户端套接字
    close(client_socket);

    return 0;
}
