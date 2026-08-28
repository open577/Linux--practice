#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <stdlib.h>
#include <sys/wait.h>
#define N 1024
using namespace std;
// 子进程执行代码
void ChildWrite(int wfd)
{
    int n = 0;
    int cnt = 0;
    while (true)
    {
        write(wfd, &n, 1);
        printf("child: %d\n", cnt++);
        sleep(1);
        break;
    }
}
// 父进程执行代码
void FatherRead(int rfd)
{
    char buffer[N];
    while (true)
    {
        sleep(1);
        buffer[0] = 0;
        ssize_t n = read(rfd, buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            buffer[n] = 0;
            printf("child say:%s", buffer);
        }
        else if (n == 0)
        {
            cout << "子进程退出 我也退出" << endl;
            break;
        }
        else
            break;
    }
}
int main()
{
    // 创建管道
    //  子进程进行写 父进程进行读
    //  c -> w      f -> r
    int fd[2];
    int n = pipe(fd);
    if (n < 0)
    {
        perror("pipe file!\n");
        return 1;
    }
    cout << "fd[0]" << " " << fd[0] << endl;
    cout << "fd[1]" << " " << fd[1] << endl;
    // 创建子进程
    pid_t a = fork();
    // 子进程
    if (a == 0)
    {
        // w  关闭读端
        close(fd[0]);
        // TODO
        ChildWrite(fd[1]);
        close(fd[1]);
    }

    // 父进程  关闭写端
    close(fd[1]);
    // TODO
    FatherRead(fd[0]);
    close(fd[0]);

    int status = 0;
    int ret = waitpid(a, &status, 0); // 获取子进程的退出码
    if (ret > 0)
    {
        printf("exit code: %d, exit signal: %d\n", (status >> 8) & 0xFF, status & 0x7F);
        sleep(5);
    }
    return 0;
}