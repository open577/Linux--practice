#include<iostream>
#include <sys/wait.h>

// int main()
// {
//     pid_t pid=fork();
//     if(pid==0)
//     {
//         std::cout<<"我是一个子进程："<<getpid()<<"我即将退出"<<std::endl;
//         exit(1);
//     }

//     int statu;
//     waitpid(pid,&statu,0);
//     printf("我是父进程，收到了子进程的退出信息：signal: %d, exit code: %d, core dump: %d\n",
//     (statu & 0x7F), (statu >> 8) & 0xFF, (statu >> 7) & 0x1);
//     return 0;
//  }

int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        sleep(2);
        printf("hello bit\n");
        printf("hello bit\n");
        printf("hello bit\n");
        printf("hello bit\n");
        printf("hello bit\n");
        int a = 10;
        a /= 0;
        printf("hello bit\n");

        exit(1);
    }
    int status = 0;
    waitpid(id, &status, 0);
    printf("signal: %d, exit code: %d, core dump: %d\n",
           (status & 0x7F), (status >> 8) & 0xFF, (status >> 7) & 0x1);
}