// // #include "ThreadPool.hpp"
// // #include <memory>
// // using namespace ThreadModlue;

// #include "Log.hpp"
// #include "ThreadPool.hpp"
// #include "Task.hpp"
// #include <memory>

// using namespace ThreadPoolMoudle;
// int main()
// {
//     ThreadPool<Task> aa();
//     aa.Start();
    

//     // Enable_Console_Log_Strategy();
//     // LogMoudle::logger.EnableConsoleLogStrategy();
//     // ThreadPool<task_t> tp;
//     // ThreadPool<task_t> tp1 = tp;
//     // ThreadPool<task_t> *tp = new ThreadPool<task_t>();
//     return 0;
// }

#pragma once
#include "ThreadPool.hpp"
#include <chrono>
#include <thread>

using namespace ThreadPoolMoudle;
using namespace LogMoudle;

int main()
{
    // 1. 选择日志策略（控制台 / 文件）
    Enable_Console_Log_Strategy();

    // 2. 定义任务类型：一个无参无返回的可调用对象
    //    ThreadPool<task_t> 中的 T 就是任务类型
    using task_t = std::function<void()>;

    // 3. 创建线程池，默认 5 个线程
    ThreadPool<task_t> tp(5);

    // 4. 启动线程池（让工作线程跑起来，等待任务）
    tp.Start();

    // 5. 投递任务
    for (int i = 0; i < 10; i++)
    {
        tp.Enqueue([i]()
                   {
            LOG(LogLevel::INFO) << "处理任务 " << i << "，线程ID: " << pthread_self();
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); });
    }

    // 6. 等任务处理完（简单粗暴地睡一会儿）
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // 7. 停止线程池，让所有工作线程退出
    tp.Stop();

    // 8. 回收线程
    tp.Join();

    LOG(LogLevel::INFO) << "主线程结束";
    return 0;
}