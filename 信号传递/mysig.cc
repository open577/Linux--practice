#include <iostream>
#include <signal.h>
#include <unistd.h>

void PrintPending(sigset_t &pending)
{
    printf("我是一个进程(%d), pending: ", getpid());
    for (int signo = 31; signo >= 1; signo--)
    {
        if (sigismember(&pending, signo))
        {
            std::cout << "1";
        }
        else
        {
            std::cout << "0";
        }
    }
    std::cout << std::endl;
}

void handler(int sig)
{
    std::cout << "#######################" << std::endl;
    std::cout << "递达" << sig << "信号!" << std::endl;
    sigset_t pending;
    int m = sigpending(&pending);
    PrintPending(pending); // 0000 0010(处理完，2号才回被设置为0)，0000 0000(执行handler方法之前，2对应的pending已经被清理了)
    std::cout << "#######################" << std::endl;
}

int main()
{
    signal(SIGINT, handler);
    // 1. 屏蔽2号信号
    sigset_t block, oblock;
    sigemptyset(&block);
    sigemptyset(&oblock);

    sigaddset(&block, SIGINT); // 已经对2号信号进行屏蔽了吗？没有！
    // for(int i = 1; i<32; i++)
    //     sigaddset(&block, i);

    int n = sigprocmask(SIG_SETMASK, &block, &oblock);
    (void)n;

    // 4. 重复获取打印过程
    int cnt = 0;
    while (true)
    {
        // 2. 获取pending信号集合
        sigset_t pending;
        int m = sigpending(&pending);

        // 3. 打印
        PrintPending(pending);
        if (cnt == 30)
        {
            // 5. 恢复对2号信号的block情况
            std::cout << "解除对2号的屏蔽" << std::endl;
            sigprocmask(SIG_SETMASK, &oblock, nullptr);
        }

        sleep(1);
        cnt++;
    }

    return 0;
}

// void SigPrint(sigset_t &block);
// void header(int sig)
// {
//     std::cout << "#########################" << std::endl;
//     std::cout << "我是一个进程：" << getpid() << " " << "我收到了一个信号：" << sig << std::endl;
//     sigset_t signum;
//     sigpending(&signum);
//     SigPrint(signum);
//     std::cout << "#########################" << std::endl;
// }
// 修改black表
// void SigPrint(sigset_t &block)
// {
//     std::cout << "我是一个进程：" << getpid() << std::endl;
//     std::cout << "这是我的block表" << std::endl;

//     for (int i = 31; i > 0; i--)
//     {
//         if (sigismember(&block, i))
//         {
//             std::cout << "1";
//         }

//         else
//             std::cout << "0";
//     }

//     std::cout << std::endl;
// }
// int main()
// {
//     signal(SIGINT, header);
//     sigset_t block, odblock;
//     int n1 = sigemptyset(&block); // 置0
//     if (n1 != 0)
//     {
//         std::cout << "sigemptyset fill!" << std::endl;
//         exit(1);
//     }
//     int n2 = sigemptyset(&odblock);
//     if (n2 != 0)
//     {
//         std::cout << "sigemptyset fill!" << std::endl;
//         exit(2);
//     }
//     int n3=sigaddset(&block, SIGINT); // 将二号信号添加到block表中   
//     if(n3!=0)
//     {
//         std::cout<<"sigaddset fill!"<<std::endl;
//         exit(3);

//     }
//     int n4=sigprocmask(SIG_SETMASK, &block, &odblock); // 将block表设置到内核block表中
//     if(n4!=0)
//     {
//         std::cout<<"sigprocmask fill!"<<std::endl;
//         exit(4);
//     }  
//     int cnt = 0;
//     while (true)
//     {
//         sigset_t sigblock;
//         sigpending(&sigblock);
//         SigPrint(sigblock);
//         if (cnt == 30)
//         {
//             sigprocmask(SIG_SETMASK, &odblock, nullptr); // 恢复2号信号
//             std::cout << "恢复2号信号的屏蔽" << std::endl;
//         }
//         cnt++;
//         sleep(1);
//     }

//     return 0;
// }

// void hander(int sig)
// {
//     std::cout<<"收到了一个信号："<<" "<<sig<<std::endl;
//     if(sig==14)
//     exit(1);
// }
// //设置闹钟  alarm 发送SIGALRM 14号信号
// int main()
// {
//     int cnt=0;
//      signal(SIGALRM,hander);
//     alarm(1);
//     while(true)
//     {
//         std::cout<<"我正在执行:"<<cnt++<<std::endl;
//     }
//     return 0;
// }

// 查看都有哪些信号不能被捕捉
// void hander(int sig)
// {
//     std::cout<<"收到了一个信号："<<" "<<sig<<" "<<"我可以被捕捉"<<" "<<std::endl;
// }
// int main()
// {
//     for(int i=0;i<32;i++)
//     {
//         signal(i,hander);
//     }

//     for(int i=0;i<32;i++)
//     {
//         sleep(1);
//         if(i==9||i==19)
//             continue;
//         raise(i);
//     }

//     return 0;
// }

// void hander(int sig)
// {
//     std::cout<<"收到了一个信号："<<" "<<sig<<" "<<std::endl;
// }
// int main()
// {
//     signal(2,hander);
//     while(true)
//     {
//         std::cout<<"我是一个进程："<<getpid()<<" "<<"我正在执行程序"<<" "<<std::endl;
//         sleep(1);
//     }
//     return 0;
// }
