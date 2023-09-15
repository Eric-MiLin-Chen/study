#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    // 创建UDP套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // 设置服务器地址和端口
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // 服务器端口号
    serverAddr.sin_addr.s_addr = inet_addr("服务器IP地址");

    // 发送消息到服务器
    const char *message = "Hello, UDP Server!";
    ssize_t bytesSent = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (bytesSent == -1)
    {
        std::cerr << "Error sending data" << std::endl;
        close(sockfd);
        return 1;
    }

    // 接收服务器的响应
    char buffer[1024];
    ssize_t bytesReceived = recvfrom(sockfd, buffer, sizeof(buffer), 0, nullptr, nullptr);
    if (bytesReceived == -1)
    {
        std::cerr << "Error receiving data" << std::endl;
        close(sockfd);
        return 1;
    }

    buffer[bytesReceived] = '\0';
    std::cout << "Received response from server: " << buffer << std::endl;

    close(sockfd);

    return 0;
}
