#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


void Waitall(int signum)
{
    waitpid(signum,nullptr,0);
    std::cout<<"父进程获得一个ID："<<signum<<std::endl;
}
int main()
{
    signal(SIGCHLD,Waitall);
    pid_t n=fork();
    if(n==0)
    {
        sleep(3);
        std::cout<<"我是子进程："<<getpid()<<" "<<"exit"<<std::endl;
        //exit(2);
        pause();
    }
    waitpid(n,nullptr,WNOHANG);
    while(true)
    {
        std::cout<<"我是父进程"<<std::endl;
        sleep(1);
    }
    return 0;
}


// int main(void)
// {
//     pid_t pid = fork();
//     if (pid == 0) {
//         _exit(0);               // 子进程立即退出
//     }

//     int status;
//     // WNOHANG:没有已退出的子进程时,立即返回 0,不阻塞
//     pid_t ret = waitpid(pid, &status,0);
//     if (ret == 0)
//         printf("子进程还没退出,waitpid 立即返回了\n");
//     else if (ret == pid)
//         printf("收掉了子进程 %d\n", pid);
//     return 0;
// }



// #include <stdio.h>
// #include <signal.h>
// #include <unistd.h>

// int flag = 0;                      // 故意先不加 volatile

// void handler(int sig) { flag = 1; }

// int main(void)
// {
//     signal(SIGINT, handler);
//     printf("pid=%d, waiting Ctrl+C...\n", getpid());
//     while (flag == 0)
//         ;                          // 空转等待
//     printf("正常退出\n");
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <unistd.h>

// typedef struct node { int val; struct node *next; } node_t;

// node_t *head = NULL;

// void handler(int sig)                 // 第二条执行流:也往同一个链表头插
// {
//     node_t *n = (node_t *)malloc(sizeof(node_t));
//     n->val = -1;
//     n->next = head;
//     head = n;
// }

// int main(void)
// {
//     signal(SIGALRM, handler);
//     alarm(1);                          // 1 秒后,handler 打断 main

//     for (int i = 0; i < 5000; i++) {   // 插得足够慢,保证 alarm 落在插入区间内
//         node_t *n = (node_t *)malloc(sizeof(node_t));
//         n->val = i;
//         n->next = head;                // ← 若 alarm 恰好在此刻打断 main
//         head = n;                      // ← handler 插入的节点将在这里被"跳过"
//         usleep(500);                   // 500 微秒 × 5000 次 ≈ 2.5 秒
//     }

//     int cnt = 0;
//     for (node_t *p = head; p; p = p->next) cnt++;
//     printf("expect=5001 actual=%d\n", cnt);   // actual < 5001 即发生了节点丢失
//     return 0;
// }
// void headler(int signum)
// {
//     write(STDOUT_FILENO, "handler 进入\n", 15);
//     sleep(3);
//     write(STDOUT_FILENO, "handler 进入\n", 15);
// }

// int main()
// {
//     struct sigaction act;
//     act.sa_handler = headler;
//     sigemptyset(&act.sa_mask);
//     act.sa_flags=0;
//     sigaction(SIGINT,&act,nullptr);
//     while(true)
//     {
//         pause();
//     }
//     return 0;
// }

// void handler(int signum)
// {
//     std::cout << "signum:" << signum << std::endl;
//     while (true)
//     {
//         sigset_t pending;
//         int n = sigpending(&pending);

//         for (int i = 31; i > 0; i--)
//         {
//             if (sigismember(&pending, i))
//             {
//                 std::cout << "1";
//             }
//             else
//                 std::cout << "0";
//         }
//         sleep(1);
//         std::cout << std::endl;
//     }
// }

// int main()
// {
//     struct sigaction oct, od;
//     oct.sa_handler = handler;
//     sigemptyset(&oct.sa_mask);

//     sigaddset(&oct.sa_mask, 3);
//     sigaddset(&oct.sa_mask, 4);
//     oct.sa_flags = 0;
//     sigaction(SIGINT, &oct, &od); // 对2号信号进行了捕捉

//     while (true)
//     {
//         std::cout << "hello world: " << getpid() << std::endl;
//         sleep(1);
//     }
//     return 0;
// }

// #include <iostream>
// #include <signal.h>

// void handler(int signum)
// {
//     std::cout << "signum:" << signum << std::endl;
//     while (true)
//     {
//         sigset_t pending;
//         int n = sigpending(&pending);

//         for (int i = 31; i > 0; i--)
//         {
//             if (sigismember(&pending, i))
//             {
//                 std::cout<<"1";
//             }
//             else
//                 std::cout<<"0";
//         }
//         sleep(1);
//         std::cout<<std::endl;
//     }
// }

// int main()
// {
//     struct sigaction oct,od;
//     oct.sa_handler=handler;
//     sigemptyset(&oct.sa_mask);
//     oct.sa_flags = 0;
//     sigaction(SIGINT, &oct, &od); // 对2号信号进行了捕捉, 2,3,4都屏蔽

//     while(true)
//     {
//         std::cout << "hello world: " << getpid() << std::endl;
//         sleep(1);
//     }
//     return 0;
// }