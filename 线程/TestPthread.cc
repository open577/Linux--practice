#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>

int flag=100;

#include <thread>
// void hello()
// {
//     int cnt=5;
//     while (cnt)
//     {
//         std::cout<<"我是子线程"<<std::endl;
//         sleep(1);
//         cnt--;
//     }
// }
// int main()
// {
//     std::thread t(hello);
//     int cnt=5;
//     while (cnt)
//     {
//         std::cout<<"我是主线程"<<std::endl;
//         sleep(1);
//         cnt--;
//     }
//     t.join();
//     return 0;
// }
// C++11 函数调用
// #include <thread>
// void hello()
// {
//     int cnt=5;
//     while (cnt)
//     {
//         std::cout << "我是新线程，"<<"我的pid是：" << getpid() <<"我的tid是："<<pthread_self()<< std::endl;
//         sleep(1);
//         flag++;
//         cnt--;
//     }
// }
// int main()
// {
//     std::thread t(hello);
//     int cnt=5;
//     while (cnt)
//     {
//         std::cout << "我是主线程，我的pid是：" << getpid() << std::endl;
//         std::cout<<"flag:"<<flag<<std::endl;
//         sleep(1);
//         cnt--;
//     }
//     t.join();
//     return 0;
// }



//Linux 原生API
void *newidea(void *mes)
{
    int cnt=5;
    while (cnt)
    {
        std::string name=(char*)mes;
        std::cout << "我是新线程，我的name："<<name<<" "<<"我的pid是：" << getpid() << std::endl;
        sleep(1);
        cnt--;
    }
    return (void*)123;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, newidea, (void *)"pthread-1");
    // std::cout<<tid<<std::endl;
    printf("0x%ld\n",tid);
    int cnt=5;
    while (cnt)
    {
        std::cout << "我是主线程，我的pid是：" << getpid() << std::endl;
        sleep(1);
        cnt--;
    }
    void *val;
    pthread_join(tid,&val);
    std::cout << "ret is : " << (long long int)val << std::endl;
    return 0;
}