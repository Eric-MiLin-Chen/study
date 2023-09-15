#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h> //包含struct sockaddr_in
#include <string>	   //包含memset()

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8888
const int RECONNECT_EXIT = 4;
const int LOGIN_EXIT = 4;
const int BUF_SIZE = 1024;

int ClieConnect(int &clie_fd, const int reconnect_counter = 0)
{
	if (reconnect_counter == RECONNECT_EXIT)
	{
		printf("Connect Failed!\nExiting\n");
		return 0;
	}
	struct sockaddr_in serv_addr, clie_addr;

	clie_fd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr)); // 把这一块内存空间全部清成0；memset()用来为新申请的内存做初始化
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);					 // host to network short转成网络字节序
	inet_pton(clie_fd, SERV_IP, &serv_addr.sin_addr.s_addr); // IP字符串转成网络字节序；

	if (connect(clie_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
	{
		printf("Connect Successfully!\n");
		return 1;
	}
	else
	{
		printf("Connect Failed!\nReconnecting(%d/%d)...\n\n", reconnect_counter + 1, RECONNECT_EXIT);
		return ClieConnect(clie_fd, reconnect_counter + 1);
	}
}

int ClieLogin(const int clie_fd, char buf[], int buflen, const int login_counter = 0)
{
	if (login_counter == LOGIN_EXIT)
	{
		printf("LOGIN Failed!\nExiting\n");
		return 0;
	}
	printf("Username: ");
	fgets(buf, buflen, stdin);			// 参数1：目的缓冲区指针，参数2：缓冲区大小，参数3：源数据流；stdin：标准输入
	send(clie_fd, buf, strlen(buf), 0); // 键盘输入hello/n，fgets后buf里的是hello/n/0,strlen(buf)取的是/0之前的长度

	printf("Password: ");
	fgets(buf, buflen, stdin);			// 参数1：目的缓冲区指针，参数2：缓冲区大小，参数3：源数据流；stdin：标准输入
	send(clie_fd, buf, strlen(buf), 0); // 键盘输入hello/n，fgets后buf里的是hello/n/0,strlen(buf)取的是/0之前的长度

	recv(clie_fd, buf, buflen, 0); // 从客户端套接字读取数据

	if (strcmp(buf, "T") == 0)
	{
		printf("Login Successfully!\n");
		return 1;
	}
	else
	{
		printf("Username or password is incorrect!\nTry to relogin again(%d/%d)\n", login_counter + 1, LOGIN_EXIT);
		return ClieLogin(clie_fd, buf, buflen, login_counter + 1);
	}
}

void Service(const int clie_fd, char buf[], int buflen)
{
	while (true)
	{
		fgets(buf, buflen, stdin);			// 参数1：目的缓冲区指针，参数2：缓冲区大小，参数3：源数据流；stdin：标准输入
		send(clie_fd, buf, strlen(buf), 0); // 键盘输入hello/n，fgets后buf里的是hello/n/0,strlen(buf)取的是/0之前的长度
		// printf("数据发送成功！\n");
		int n = recv(clie_fd, buf, buflen, 0); // 写完之后发给服务端了，服务端会响应回来，现在该读了
		if (buf[0] != '\n' && n == 1)
		{
			printf("Log Out!\n");
			return;
		}
		write(STDOUT_FILENO, buf, n); // 把读到的服务器的响应写到屏幕
	}
}

int main()
{
	int clie_fd;
	char buf[BUF_SIZE]; // BUFSIZ是内置的宏，专门用来指定buf大小

	if (ClieConnect(clie_fd))
	{
		if (ClieLogin(clie_fd, buf, sizeof(buf)))
			Service(clie_fd, buf, sizeof(buf));
		close(clie_fd);
	}
	return 0;
}
