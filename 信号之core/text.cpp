#include <iostream>
#include <sys/wait.h>

int main()
{
    pid_t n=fork();
    if(n==0)
    {
        //子进程
        // while(1)
        // {
        //     sleep(4);
        //     int b=10/0;
        // }

        std::cout<<"done"<<std::endl;
    }
    int status;
    waitpid(n, &status, 0);

    if (WIFEXITED(status)) // 正常退出（exit / 从 main return）
        printf("exit code = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
    { // 被信号杀死
        printf("killed by signal %d\n", WTERMSIG(status));
        if (WCOREDUMP(status)) // 仅在 WIFSIGNALED 为真时才能用
            printf("并且留下了 core 文件\n");
    }
    return 0;
}