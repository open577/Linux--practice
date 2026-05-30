//#include<stdio.h>
//#include<unistd.h>
//int main()
//{
//    int ret=fork();
//    if(ret==0)
//    {
//        while(1)
//        {
//        printf("我是一个子进程：%d\n,我的父进程是：%d\n",getpid(),getppid());
//        sleep(1);
//        }
//    }
//
//    else if(ret>0)
//
//    {
//        while(1)
//        {
//
//    
//        }
//    }
//    return 0;
//}

#include <stdio.h>
#include <unistd.h>
//
//int main() {
//    FILE *fp = fopen("/tmp/test.txt", "w");
//    
//    while (1) {
//        // 频繁写磁盘 → 会进入 D 状态（不可中断睡眠）
//        fwrite("aaa", 1, 3, fp);
//        fflush(fp);  // 强制刷到磁盘
//    }
//    
//    fclose(fp);
//    return 0;
//}

#include <stdio.h>
int main() {
    printf("我的进程：%d\n",getpid());
    while (1) {
        int x;
        scanf("%d", &x); // 平时是 S
        printf("ok\n");
    }
}
