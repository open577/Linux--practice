#include <stdio.h>
#include <stdio.h>   
#include <stdlib.h>  
#include <fcntl.h>   
#include <unistd.h> 
int main() {
    printf("stdin fd:  %d\n", fileno(stdin));
    printf("stdout fd: %d\n", fileno(stdout));
    printf("stderr fd: %d\n", fileno(stderr));
    
//    int fd1, fd2, fd3, fd4;   
//    fd1 = open("/dev/null", O_RDONLY);
//    if (fd1 == -1) { perror("open failed"); exit(1); }
//
//    fd2 = open("/dev/null", O_RDONLY);
//    if (fd2 == -1) { perror("open failed"); exit(1); }
//
//    fd3 = open("/dev/null", O_RDONLY);
//    if (fd3 == -1) { perror("open failed"); exit(1); }
//
//    fd4 = open("/dev/null", O_RDONLY);
//    if (fd4 == -1) { perror("open failed"); exit(1); }
//
//    // 3. 按照图片格式打印结果
//    printf("fd1: %d\n", fd1);
//    printf("fd2: %d\n", fd2);
//    printf("fd3: %d\n", fd3);
//    printf("fd4: %d\n", fd4);
//
//    close(fd1);
//    close(fd2);
//    close(fd3);
//    close(fd4);
    // 模拟重定向
    close(1); // 1. 释放 1 号坑位
    int fd_log = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // 2. 抢占 1 号坑位
    // 此时 fd_log 的值一定是 1
    printf("Log file fd is: %d\n", fd_log); // 注意：这行 printf 不会显示在屏幕上，而是写进了 log.txt！
    return 0;
}
