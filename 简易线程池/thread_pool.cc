#include <iostream>
#include <pthread.h>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstdio>

int num = 10;

void *routine(void *mes)
{
    std::string name = static_cast<const char*>(mes);
    delete [] (char*)mes;
    std::cout << "我是子线程：" << name<< std::endl;
    return nullptr;
}

int main()
{
    std::vector<pthread_t> meanger;
    for (int i = 0; i < num; i++)
    {
        sleep(1);
        char *id=new char[64];
        pthread_t tid;
        snprintf(id,64,"thread-%d",i);
        int n = pthread_create(&tid, nullptr, routine, (void *)id);
        //sleep(1);
        if (n == 0)
        {
            meanger.push_back(tid);
        }
    }

    for(auto t:meanger)
    {
        sleep(1);
        int n=pthread_join(t,nullptr);
        if(n==0)
        {
            std::cout<<"子线程回收成功"<<std::endl;
        }
    }
    return 0;
}