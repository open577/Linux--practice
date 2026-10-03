#pragma once
#include <iostream>
#include <unistd.h>
#include <functional>

// 任务形式2
// 我们定义了一个任务类型，返回值void，参数为空
using task_t = std::function<void()>;

void Download()
{
    std::cout << "我是一个下载任务..." << std::endl;
    sleep(3); // 假设处理任务比较耗时
}

// 任务形式1
class Task
{
public:
    Task() {}
    Task(int x, int y) : _x(x), _y(y)
    {
    }
    void Execute()
    {
        _result = _x + _y;
    }
    int X() { return _x; }
    int Y() { return _y; }
    int Result()
    {
        return _result;
    }

private:
    int _x;
    int _y;
    int _result;
};