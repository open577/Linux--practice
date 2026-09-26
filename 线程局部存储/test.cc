#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>

__thread int a=10;

std::string Addr(int &num)
{
    char a[64];
    snprintf(a,sizeof(a),"%p",&num);
    return a;
}

void *routine1(void *mes)
{
    while(true)
    {
        std::cout<<"我是线程1，a的值为:"<<a++<<" "<<"a的地址："<<Addr(a)<<std::endl;
        sleep(1);
    }
    return nullptr;
}

void *routine2(void *mes)
{
    while(true)
    {
        std::cout<<"我是线程2，a的值为:"<<a  <<" "<<"a的地址："<<Addr(a)<<std::endl;
        sleep(1);
    }
    return nullptr;
}

int main()
{
    pthread_t tid1,tid2;
    pthread_create(&tid1,nullptr,routine1,nullptr);
    pthread_create(&tid2,nullptr,routine2,nullptr);

    pthread_join(tid1,nullptr);
    pthread_join(tid2,nullptr);
    return 0;
}