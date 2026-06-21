#include <stdio.h>
#include <string.h> // 必须引入这个头文件来使用 strcmp
#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include <sys/types.h>

int main()
{
    // 父进程里的本地变量
    int a = 10;

    pid_t pid = fork(); // 创建子进程

    if (pid == 0) {
        // ==================
        // 子进程
        // ==================
        a = 20;  // 子进程改自己的 a
        printf("子进程：a = %d\n", a);
    }
    else {
        // ==================
        // 父进程
        // ==================
        wait(NULL); // 等子进程跑完
        printf("父进程：a = %d\n", a);
    }

    return 0;
}

//// main 三参数：argc, argv, envp（环境变量）
//int main(int argc, char *argv[], char *envp[])
//{
//    pid_t pid = fork(); // 创建子进程
//
//    if (pid == -1) {
//        perror("fork失败");
//        return 1;
//    }
//
//    if (pid == 0) {
//        // ====================
//        // 子进程
//        // ====================
//        //printf("%s\n",argv[1]);
//        printf("===== 子进程 PID = %d =====\n", getpid());
//        for (int i = 0; i < 5 && envp[i] != NULL; i++) {
//            printf("子进程 envp[%d] = %s\n", i, envp[i]);
//        }
//    } else {
//        // ====================
//        // 父进程
//        // ====================
//        //printf("%s\n",argv[1]);
//        printf("===== 父进程 PID = %d =====\n", getpid());
//        for (int i = 0; i < 5 && envp[i] != NULL; i++) {
//            printf("父进程 envp[%d] = %s\n", i, envp[i]);
//        }
//
//        // 等待子进程结束（避免输出混乱）
//        wait(NULL);
//    }
//
//    return 0;
//}
//
//#include <stdlib.h>
//int main()
//{
//    printf("当前用户：%s\n", getenv("USER"));
//    printf("家目录：%s\n", getenv("HOME"));
//    printf("当前路径：%s\n", getenv("PWD"));
//    return 0;
//}
//extern char **environ;
//
//int main()
//{
//    for(int i = 0; environ[i] != NULL; i++)
//    {
//        printf("%s\n", environ[i]);
//    }
//    return 0;
//}


//// 三参数 main，envp 指向环境变量数组
//int main(int argc, char *argv[], char *envp[])
//{
//    printf("=== 前5个环境变量 ===\n");
//
//    for (int i = 0; i < 5 && envp[i] != NULL; i++) {
//        printf("envp[%d]: %s\n", i, envp[i]);
//    }
//
//    return 0;
//}
//

//int main(int argc, char *argv[], char *envp[])
//{
//    printf("%d\n",argc);
//    // 先确保用户至少输入了一个额外的命令行参数
//    if (argc > 1) 
//    {
//        // argv[0] 是程序名自己（"./text.exe"）
//        // argv[1] 才是你输入的第一个真正参数（比如 a 或 b）
//        
//        if (strcmp(argv[1], "a") == 0) // strcmp 返回 0 代表字符串完全相等
//        {
//            printf("a\n");
//        }
//        else if (strcmp(argv[1], "b") == 0)
//        {
//            printf("b\n");
//        }
//    }
//    else 
//    {
//        printf("请在运行程序时传入参数 a 或 b！\n");
//    }
//
//    return 0;
//}

//int main()
//{
//    printf("hello world\n");
//    return 0;
//}
//

//#include <stdio.h>
//
//// 三参数 main
//int main(int argc, char *argv[], char *envp[])
//{
//    // 1. 打印参数个数
//    printf("参数个数 argc = %d\n", argc);
//
//    // 2. 打印所有命令行参数
//    printf("\n命令行参数 argv:\n");
//    for (int i = 0; i < argc; i++) {
//        printf("argv[%d] = %s\n", i, argv[i]);
//    }
//
//    // 3. 打印前5个环境变量（envp 以 NULL 结尾）
//    printf("\n环境变量 envp (前5个):\n");
//    for (int i = 0; envp[i] && i < 5; i++) {
//        printf("envp[%d] = %s\n", i, envp[i]);
//    }
//
//    return 0;
//}
