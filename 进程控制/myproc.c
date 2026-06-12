#define _GNU_SOURCE
////#include<stdio.h>
////int main()
////{
////    printf("hello\n");
////    return 0;
////}
//
//#include <stdio.h>
//#include <unistd.h>
//#include <sys/types.h>
//#include<stdlib.h>
////int main(void) {
////    pid_t pid;
////    printf("Before: pid is %d\n", getpid());
////    if ((pid = fork()) == -1) {
////        perror("fork()");
////        exit(1);
////    }
////    printf("After: pid is %d, fork return %d\n", getpid(), pid);
////    sleep(1);
////    return 0;
////}
////
//
//#include <unistd.h>
//#include <signal.h>
//
//int main(void)
//{
//    kill(getpid(), SIGKILL);
//    return 0;
//}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//int main() {
//    printf("hello"); // 未加\n，数据存在缓冲区
//    sleep(1);
//    printf("\n");
//    exit(0);        // 会刷新缓冲区，输出hello
//}

#include <stdio.h>
#include <unistd.h>

//int main() {
//    printf("hello");
//    _exit(0);       // 不刷新缓冲区，无输出
//}

//#include<string.h>
//int main()
//{
//
//    for(int i=0;i<200;i++)
//    {
//        printf("%d->%s\n",strerror(i));
//    }
//    return 0;
//}
//
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//int main()
//{
//    int i = 0;
//    // 把 200 改成 130，因为 Linux 标准错误码一般不超过 134
//    
//    //printf("%d->%s\n", -1, strerror(-1));
//    for(; i < 200; i++)
//    {
//        char *msg = strerror(i);
//        if (msg != NULL) {
//            printf("%d->%s\n", i, msg);
//        }
//    }
//    return 0;
//}
//

#include<errno.h>
//int main()
//{
//    FILE* fp=fopen("text.xxx","r");
//    if(fp==NULL)
//        return errno;
//    return 0;
//}
//

//int main()
//{
//
//    pid_t t=fork();
//    if(t==0)
//    {
//        printf("我是一个子进程:%d\n",getpid());
//        sleep(5);
//    }
//
//    else
//        while(1)
//        {
//            sleep(1);
//            printf("我是一个父进程%d\n",getpid());
//        }
//    return 0;
//}
//

//int main()
//{
//
//    pid_t t=fork();
//    if(t==0)
//    {
//        printf("我是一个子进程:%d\n",getpid());
//        sleep(5);
//    }
//
//    else
//    {
//    
//        wait(NULL);
//        while(1)
//        {
//            sleep(1);
//            printf("我是一个父进程%d\n",getpid());
//        }
//    }
//    return 0;
//}
//
//
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//int main() {
//    pid_t pid = fork();
//
//    if (pid == 0) {
//        // 子进程：你可以改成 exit(42) 或者段错误代码测试
//        printf("我是子进程，pid=%d\n", getpid());
//        sleep(2);
//        // 测试1：正常退出
//        exit(42);
//        // 测试2：段错误
//        // int *p = NULL; *p = 1;
//    } else {
//        int status;
//        wait(&status); // 等子进程，同时把状态存在 status 里
//
//        if (WIFEXITED(status)) {
//            printf("✅ 子进程正常退出，退出码：%d\n", WEXITSTATUS(status));
//        } else if (WIFSIGNALED(status)) {
//            printf("❌ 子进程被信号杀死，信号号：%d\n", WTERMSIG(status));
//        }
//    }
//    return 0;
//}
//

//#include <stdio.h>
//#include <sys/wait.h>
//#include <unistd.h>
//#include <stdlib.h>
//
//int main() {
//    pid_t pid = fork();
//    if (pid == 0) {
//        printf("child is run, pid is: %d\n", getpid());
//        sleep(5);
//    
//        while(1)
//        {}
//        exit(257);
//    } else {
//        printf("我是父进程：%d\n",getpid());
//        int status = 0;
//        pid_t ret = waitpid(pid, &status, 0); // 阻塞等待
//        if (ret > 0 && WIFEXITED(status)) {
//            printf("wait success, child return code is: %d\n", WEXITSTATUS(status));
//        }
//    }
//    return 0;
//}
//

//#include <stdio.h>
//#include <sys/wait.h>
//#include <unistd.h>
//#include <stdlib.h>
//
//int main() {
//    pid_t pid = fork();
//    if (pid == 0) {
//        while(1)
//        {
//            printf("child is run, pid is: %d\n", getpid());
//            sleep(1);
//            exit(15);
//        }
//    } 
//    
//    else
//    {
//        // 父进程：非阻塞轮询等待子进程
//        int status;
//        pid_t ret;
//        while (1)
//        {
//            // WNOHANG 非阻塞：子进程未退出则直接返回0
//            ret = waitpid(pid, &status, WNOHANG);
//            if (ret == 0)
//            {
//                // 子进程仍在运行，父进程打印信息并休眠1秒
//                printf("我是一个父进程\n");
//                sleep(1);
//            }
//            else if (ret > 0)
//            {
//                // 等待到子进程，退出循环
//                printf("父进程：已成功回收子进程 PID = %d\n", ret);
//                break;
//            }
//            else
//            {
//                perror("waitpid failed");
//                break;
//            }
//        }
//    }
//    return 0;
//}
//
//
//#include <stdio.h>
//#include <sys/wait.h>
//#include <unistd.h>
//#include <stdlib.h>
//int main() {
//    pid_t pid = fork();
//    if (pid == 0) {
//        printf("child is run, pid is: %d\n", getpid());
//        sleep(5);
//    
//        while(1)
//        {}
//        exit(257);
//    } else {
//        int status = 0;
//        pid_t ret = waitpid(pid, &status,  WNOHANG); // 阻塞等待
//        while(1)
//        {
//            sleep(1);
//            printf("我是父进程：%d\n",getpid());
//        }
//        if (ret > 0 && WIFEXITED(status)) {
//            printf("wait success, child return code is: %d\n", WEXITSTATUS(status));
//        }
//    }
//    return 0;
//}
//

//#include <stdio.h>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <stdlib.h>
//
char *newnew = (char*)"myVAL=66666666";
char *const addenv[] = {
    (char *const)"MYVAL=123456789",
    (char *const)"MYVAL1=123456789",
    (char *const)"MYVAL2=123456789",
    NULL
};

int main()
{
    printf("我的程序要运行了!\n");
    if(fork() == 0)
    {
        printf("I am Child, My Pid Is: %d\n", getpid());
        sleep(1);

        char *const argv[] = {
            (char*const)"other",
            (char*const)"-a",
            (char*const)"-b",
            (char*const)"-c",
           (char*const)"-d",
                       NULL
            };

        for(int i = 0; addenv[i]; i++)        {
            putenv(addenv[i]);

        }
        extern char **environ;
        execvpe("./other", argv, environ);
        
        //putenv(newnew);
        //execvp("./other", argv);
        //execv("/usr/bin/ls", argv);
        //extern char** environ;
        //execve("/home/wyy/my-project/linux-practice/进程控制/other", argv,addenv);
        //execlp("/usr/bin/ls", "ls", "-ln", "-a", NULL);
        //child
        //execl("/usr/bin/ls", "/usr/bin/ls", "-ln", "-a", NULL);
        //execl("./other", "other", NULL);
        //execl("/usr/bin/python3", "python", "other.py", NULL);
        //execl("/usr/bin/bash", "bash", "other.sh", NULL);
        exit(1);
    }

    waitpid(-1, NULL, 0);
    printf("我的程序运行完毕了\n");
    //return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//int main() {
//    pid_t pid = fork();
//    if (pid == -1) {
//        perror("fork");
//        exit(EXIT_FAILURE);
//    }
//
//    if (pid == 0) {
//        // 子进程：用 execl 执行 /bin/ls -l
//        // 参数列表必须以 NULL 结尾
//        execl("/bin/ls", "ls", "-l", NULL);
//
//        // 如果 execl 成功，下面的代码不会执行
//        perror("execl failed");
//        exit(EXIT_FAILURE);
//    } else {
//        // 父进程等待子进程结束
//        wait(NULL);
//        printf("execl 测试完成\n");
//    }
//
//    return 0;
//}
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/wait.h>
//
//int main() {
//    pid_t pid = fork();
//    if (pid == -1) {
//        perror("fork");
//        exit(EXIT_FAILURE);
//    }
//
//    if (pid == 0) {
//        // 子进程：用 execlp 执行 ls -a
//        // 不用写 /bin/ls，会自动从 PATH 找
//        execlp("ls", "ls", "-a", NULL);
//
//        perror("execlp failed");
//        exit(EXIT_FAILURE);
//    } else {
//        wait(NULL);
//        printf("execlp 测试完成\n");
//    }
//
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//int main() {
//    // 自定义环境变量列表，必须以 NULL 结尾
//    char *const env[] = {
//        "MY_NAME=Tom",
//        "MY_AGE=18",
//        NULL
//    };
//
//    pid_t pid = fork();
//    if (pid == -1) {
//        perror("fork");
//        exit(EXIT_FAILURE);
//    }
//
//    if (pid == 0) {
//        // 子进程：用 execle 执行 /usr/bin/env，查看环境变量
//        execle("/usr/bin/env", "env", NULL, env);
//
//        perror("execle failed");
//        exit(EXIT_FAILURE);
//    } else {
//        wait(NULL);
//        printf("execle 测试完成\n");
//    }
//
//    return 0;
//}
//

//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/wait.h>
//
//int main() {
//    pid_t pid = fork();
//    if (pid == -1) {
//        perror("fork");
//        exit(EXIT_FAILURE);
//    }
//
//    if (pid == 0) {
//        // 子进程：用 execv 执行 /bin/ls -lh
//        // 参数数组必须以 NULL 结尾
//        char *const argv[] = {"ls", "-lh", NULL};
//        execv("/bin/ls", argv);
//
//        perror("execv failed");
//        exit(EXIT_FAILURE);
//    } else {
//        wait(NULL);
//        printf("execv 测试完成\n");
//    }
//
//    return 0;
//}



