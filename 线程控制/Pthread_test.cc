#include<iostream>
#include<pthread.h>
#include<unistd.h>

#include <stdio.h>
















void *newidea(void *mes)
{
    int a=10/0;
    return (void*)123;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, newidea, (void *)"pthread-1");
    void *val;
    pthread_join(tid,&val);
    return 0;
}






// void *worker(void *arg)
// {
//     (void)arg;
//     volatile long long cnt = 0;
//     while (1)
//     {
//         cnt++;
//         // 实验 A：什么都不加。纯计算循环不调用任何函数，
//         //         没有任何取消点，cancel 请求只能一直挂着。
//         //         （刻意不 printf：它要往 stdout 写，某些实现里
//         //           也可能被做成取消点，会污染实验）
//         // 实验 B：把这行注释打开，循环里有了手动取消点
//         // pthread_testcancel();
//     }
//     return NULL;
// }

// int main()
// {
//     pthread_t tid;
//     pthread_create(&tid, NULL, worker, NULL);

//     sleep(1);              // 给新线程一点跑起来的时间
//     pthread_cancel(tid);   // 只是发一个取消"请求"，不保证停

//     void *ret = NULL;
//     pthread_join(tid, &ret);   // 等线程真的停下来
//     if (ret == PTHREAD_CANCELED)
//         printf("线程被取消，join 拿到 PTHREAD_CANCELED\n");
//     else
//         printf("join 正常返回，线程不是被取消的\n");
//     return 0;
// }


// void *newidea(void *mes)
// {
//     pthread_detach(pthread_self());
//         std::string name=(char*)mes;
//         std::cout << "我是新线程，我的name："<<name<<" "<<"我的pid是：" << getpid() << std::endl;
//         sleep(1);
//     return (void*)123;
// }

// int main()
// {
//     pthread_t tid;
//     pthread_create(&tid, nullptr, newidea, (void *)"pthread-1");
//     sleep(2);
//     pthread_detach(pthread_self());
//     sleep(2);
//     void *val;
//     pthread_join(tid,&val);
//     std::cout << "ret is : " << (long long int)val << std::endl;
//     return 0;
// }

// class Task
// {
// public:
//     Task(int a, int b) : _a(a), _b(b) {}
//     int Execute()
//     {
//         return _a + _b;
//     }
//     ~Task() {}

// private:
//     int _a;
//     int _b;
// };

// class Result
// {
// public:
//     Result(int result) : _result(result)
//     {
//     }
//     int GetResult() { return _result; }
//     ~Result() {}
// private:
//     int _result;
// };

// void *routine(void *tem)
// {
//     Task * t=(Task*)tem;
//     Result *result=new Result(t->Execute());
//     std::cout<<"结果是"<<result->GetResult()<<std::endl;
//     delete result;
//     // return nullptr;
//     pthread_exit(result);
// }
// int main()
// {
//     Task *t  = new Task(10,20);
//     pthread_t tid;
//     pthread_create(&tid,nullptr,routine,(void *)t);

//     void *statu=nullptr;
//     pthread_join(tid,&statu);
//     Result *res=(Result*)statu;
//     std::cout<<"退出码为："<<res->GetResult()<<std::endl;
//     delete t;
//     delete res;
//     return 0;
// }