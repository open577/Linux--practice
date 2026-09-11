#include <signal.h>
#include <iostream>

// int main()
// {
//     while (true)
//     {
//         std::cout << "进程：" << getpid() << "即将结束" << std::endl;
//         sleep(2);
//         int n = kill(getpid(), 2);
//     }

//     return 0;
// }

// int main()
// {
//     while (true)
//     {
//         std::cout << "进程：" << getpid() << std::endl;
//         abort();
//     }
//     return 0;
// }

// int main()
// {
//     while(true)
//     {
//         std::cout<<"我是一个进程："<<getpid()<<std::endl;
//         sleep(1);
//     }
//     return 0;
// }

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        std::cout<<"please enter right"<<std::endl;
        return 1;
    }

    int sig=std::stoi(argv[1]);
    int pid=std::stoi(argv[2]);

    int n=kill(pid,sig);
    if(n==0)
    {
        std::cout<<"send" <<" "<<sig<<" "<<"to"<<" "<<pid<<" "<<"success"<<std::endl;
    }
    return 0;
}