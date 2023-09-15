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

    // 绑定服务器地址和端口
    struct sockaddr_in serverAddr, clientAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // 服务器端口号
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error binding socket" << std::endl;
        close(sockfd);
        return 1;
    }

    // 接收消息并回应
    char buffer[1024];
    socklen_t clientAddrLen = sizeof(clientAddr);

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesReceived = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (bytesReceived == -1)
        {
            std::cerr << "Error receiving data" << std::endl;
            close(sockfd);
            return 1;
        }

        std::cout << "Received message from " << inet_ntoa(clientAddr.sin_addr) << ": " << buffer << std::endl;

        // 回应客户端
        sendto(sockfd, buffer, bytesReceived, 0, (struct sockaddr *)&clientAddr, clientAddrLen);
    }

    close(sockfd);

    return 0;
}
