#include <iostream>
#include <string>
#include <mutex>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include "Mutex.hpp"
using MutexModule::Mutex;
using MutexModule::LockGrund;

int ticket = 1000;
class ThreadData
{
public:
    ThreadData(const std::string &name, Mutex *lock)
        : _name(name), _lockp(lock)
    {
    }
    std::string _name;
    Mutex *_lockp;
};

void *routine(void *mes)
{
    ThreadData *tmp = static_cast<ThreadData *>(mes);

    while (true)
    {
        LockGrund lock(*tmp->_lockp);
        if (ticket > 0)
        {
            usleep(1000);
            printf("我是%s,我正在抢票:%d\n", tmp->_name.c_str(), ticket);
            ticket--;
        }

        else
        {

            break;
        }
        usleep(123);
    }
    return nullptr;
}
int main()
{

    Mutex mutex;
    pthread_t tid1, tid2, tid3, tid4;

    ThreadData *t1 = new ThreadData("thread-1", &mutex);
    pthread_create(&tid1, nullptr, routine, (void *)t1);

    ThreadData *t2 = new ThreadData("thread-2", &mutex);
    pthread_create(&tid2, nullptr, routine, (void *)t2);

    ThreadData *t3 = new ThreadData("thread-3", &mutex);
    pthread_create(&tid3, nullptr, routine, (void *)t3);

    ThreadData *t4 = new ThreadData("thread-4", &mutex);
    pthread_create(&tid4, nullptr, routine, (void *)t4);

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);
    pthread_join(tid3, nullptr);
    pthread_join(tid4, nullptr);
    delete t1;
    delete t2;
    delete t3;
    delete t4;
    return 0;
}
