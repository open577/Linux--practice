#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int ticket = 100;
#define NUM 5

void *routine(void *mes)
{
    std::string name = (char *)mes;
    while (true)
    {
        if (ticket > 0)
        {
            pthread_mutex_lock(&mutex);
            pthread_cond_wait(&cond,&mutex);
            std::cout << name << " " << ticket << std::endl;
            ticket++;
            pthread_mutex_unlock(&mutex);
        }

        else
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    return nullptr;
}

int main()
{
    pthread_t arr[NUM];
    for (int i = 0; i < NUM; i++)
    {
        char buf[64];
        snprintf(buf, sizeof(buf), "thread-%d", i);
        int n = pthread_create(&arr[i], nullptr, routine, (void *)buf);
        if (n != 0)
            continue;
    }
    std::cout<<"线程已经创建完毕，请稍等"<<std::endl;

    while(true)
    {
        std::cout<<"唤醒一个线程"<<std::endl;
        pthread_cond_signal(&cond);

        // std::cout<<"唤醒所有进程"<<std::endl;
        // pthread_cond_broadcast(&cond);
        std::cout<<"执行下一块"<<std::endl;
        sleep(1);
    }

    for (int i = 0; i < NUM; i++)
    {
        pthread_join(arr[i], nullptr);
    }
    return 0;
}