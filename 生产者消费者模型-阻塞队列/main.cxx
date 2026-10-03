#include "BlockQueue.hpp"
#include "Task.hpp"
using BlockQueue::Block;

void *consumer(void *mes)
{
    Block<Task> *bq = (Block<Task> *)mes;
    while (true)
    {
        sleep(1);
        Task t = bq->Pop();
        std::cout << "我是客户端，我拿到了一份数据" << "x + y =" << t.Result() << std::endl;
    }

    return nullptr;
}

void *productor(void *mes)
{
    Block<Task> *bq = (Block<Task> *)mes;
    int x = 1;
    int y = 1;
    while (true)
    {
        sleep(1);
        std::cout << "我是服务端，我生产了一份数据" << "x + y = ?" << std::endl;
        Task t(x, y);
        t.Execute();
        bq->Push(t);

        x++;
        y++;
    }
    return nullptr;
}
int main()
{
    Block<Task> *bq = new Block<Task>();

    pthread_t c[2], p[3];

    pthread_create(c, nullptr, consumer, bq);
    pthread_create(c + 1, nullptr, consumer, bq);
    pthread_create(p, nullptr, productor, bq);
    pthread_create(p + 1, nullptr, productor, bq);
    pthread_create(p + 2, nullptr, productor, bq);

    pthread_join(c[0], nullptr);
    pthread_join(c[1], nullptr);
    pthread_join(p[0], nullptr);
    pthread_join(p[1], nullptr);
    pthread_join(p[2], nullptr);
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