#include "RingQueue.hpp"
#include <unistd.h>

struct threaddata
{
    RingQueue<int> *rq;
    std::string name;
};

void *consumer(void *args)
{
    threaddata *td = static_cast<threaddata*>(args);

    while (true)
    {
        sleep(3);
        // 1. 消费任务
        int t = 0;
        td->rq->Pop(&t);

        // 2. 处理任务 -- 处理任务的时候，这个任务，已经被拿到线程的上下文中了,不属于队列了
        std::cout << td->name << " 消费者拿到了一个数据:  " << t << std::endl;
        // t();
    }
}

int data = 1;

void *productor(void *args)
{
    threaddata *td = static_cast<threaddata*>(args);
    
    while (true)
    {
        sleep(1);
        // sleep(2);
        // 1. 获得任务
        // std::cout << "生产了一个任务: " << x << "+" << y << "=?" << std::endl;
        std::cout << td->name << " 生产了一个任务: " << data << std::endl;

        // 2. 生产任务
        td->rq->Equeue(data);

        data++;
    }
}

int main()
{
    // 扩展认识: 阻塞队列: 可以放任务吗？
    // 申请阻塞队列
    RingQueue<int> *rq = new RingQueue<int>();

    // 构建生产和消费者
    // 如果我们改成多生产多消费呢？？
    // 单单: cc, pp -> 互斥关系不需要维护，互斥与同步
    // 多多：cc, pp -> 之间的互斥关系！
    pthread_t c[2], p[3];

    threaddata *td = new threaddata();
    td->name = "cthread-1";
    td->rq = rq;
    pthread_create(c, nullptr, consumer, td);

    threaddata *td2 = new threaddata();
    td2->name = "cthread-2";
    td2->rq = rq;
    pthread_create(c + 1, nullptr, consumer, td2);

    threaddata *td3 = new threaddata();
    td3->name = "pthread-3";
    td3->rq = rq;
    pthread_create(p, nullptr, productor, td3);

    threaddata *td4 = new threaddata();
    td4->name = "pthread-4";
    td4->rq = rq;
    pthread_create(p + 1, nullptr, productor, td4);

    threaddata *td5 = new threaddata();
    td5->name = "pthread-5";
    td5->rq = rq;
    pthread_create(p + 2, nullptr, productor, td5);

    pthread_join(c[0], nullptr);
    pthread_join(c[1], nullptr);
    pthread_join(p[0], nullptr);
    pthread_join(p[1], nullptr);
    pthread_join(p[2], nullptr);

    return 0;
}

// void *consumer(void *mes)
// {
//     RingQueue<int> *bq = static_cast<RingQueue<int> *>(mes);
//     while (true)
//     {
//         sleep(1);
//         int i = 0;
//         bq->Pop(&i);
//         std::cout << "我是客户端，我拿到了一份数据" << i << std::endl;
//     }

//     return nullptr;
// }

// int data = 1;
// void *productor(void *mes)
// {
//     RingQueue<int> *bq = static_cast<RingQueue<int> *>(mes);
//     while (true)
//     {
//         sleep(1);
//         std::cout << "我是服务端，我生产了一份数据" << std::endl;

//         bq->Equeue(data);

//         data++;
//     }
//     return nullptr;
// }

// int main()
// {
//     RingQueue<int> *bq = new RingQueue<int>();

//     pthread_t c[1], p[1];

//     pthread_create(&p[0], nullptr, productor, bq);

//     pthread_create(&c[0], nullptr, consumer, bq);

//     pthread_join(c[0], nullptr);
//     pthread_join(p[0], nullptr);

//     delete bq;
//     return 0;
// }

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