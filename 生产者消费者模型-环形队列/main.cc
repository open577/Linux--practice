#include "RingQueue.hpp"
#include <unistd.h>

void *consumer(void *mes)
{
    RingQueue<int> *bq = static_cast<RingQueue<int> *>(mes);
    while (true)
    {
        sleep(1);
        int i = 0;
        bq->Pop(&i);
        std::cout << "我是客户端，我拿到了一份数据" << i << std::endl;
    }

    return nullptr;
}

int data = 1;
void *productor(void *mes)
{
    RingQueue<int> *bq = static_cast<RingQueue<int> *>(mes);

    while (true)
    {
        sleep(1);
        std::cout << "我是服务端，我生产了一份数据" << std::endl;

        bq->Equeue(data);

        data++;
    }
    return nullptr;
}
int main()
{
    RingQueue<int> *bq = new RingQueue<int>();

    pthread_t c[1], p[1];

    pthread_create(&p[0], nullptr, productor, bq);

    pthread_create(&c[0], nullptr, consumer, bq);

    pthread_join(c[0], nullptr);
    pthread_join(p[0], nullptr);

    delete bq;
    return 0;
}

// int main()
// {
//     Block<Task> *bq = new Block<Task>();

//     pthread_t p, c;

//     pthread_create(&c, nullptr, consumer, (void *)bq);
//     pthread_create(&p, nullptr, productor, (void *)bq);

//     pthread_join(p, nullptr);
//     pthread_join(c, nullptr);
//     return 0;
// }