#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int pipe_fd[2], res;
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (child_pid == 0)
    { // 子进程
        // 向管道写入数据
        printf("Parent %d: %d \n", getppid(), getpid());
        const char *message = "Hello from child process!\n";
        res = lockf(pipe_fd[1], 1, 0);
        res = write(pipe_fd[1], message, strlen(message));
        res = lockf(pipe_fd[1], 0, 0);
        sleep(1);
        std::cout << "Child process exiting." << std::endl;
        printf("Parent %d: %d \n", getppid(), getpid());
    }
    else
    { // 父进程
        char buffer[1024];
        res = lockf(pipe_fd[0], 1, 0); // 关闭读端
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
        res = lockf(pipe_fd[0], 0, 0); // 关闭读端

        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            std::cout << "Received from child process: " << buffer;
        }

        // 等待子进程结束
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status))
            std::cout << "Child process exited with status: " << WEXITSTATUS(status) << std::endl;
        else
            std::cerr << "Child process did not exit normally." << std::endl;

        std::cout << "Parent process exiting." << std::endl;
    }

    return 0;
}
