#ifndef __PROCESS_POOL_HPP__
#define __PROCESS_POOL_HPP__

#include <iostream>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include "task.hpp"


class Channel
{
public:
    Channel(int wfd, pid_t subid)
        : _wfd(wfd), _subid(subid)
    {
        _name="channel-" +std::to_string(_wfd) +"--" +std::to_string(_subid);
    }

    ~Channel()
    {
    }

    void Send(int code)
    {
        int n = write(_wfd, &code, sizeof(code));
        (void)n; //  如果没有会怎么样???
    }

    void Close()
    {
        close(_wfd);
    }

    void Wait()
    {
        int n = waitpid(_subid, nullptr, 0);
        (void)n;
    }

    int Fd() { return _wfd; }
    pid_t Subid() { return _subid; }
    std::string Name() { return _name; }

private:
    int _wfd;
    pid_t _subid;
    std::string _name;
};

class ChannelManager
{
public:
    ChannelManager() : _next(0) {}
    ~ChannelManager() {}
    void Insert(int wfd, pid_t subid)
    {
        _channels.emplace_back(wfd, subid);
    }

    Channel &Select()
    {
        auto &c = _channels[_next++];
        _next = _next % _channels.size();
        return c;
    }

    void PrintChannel()
    {
        for (auto &channel : _channels)
        {
            std::cout << channel.Name() << std::endl;
        }
    }

    void StopSubprocess()
    {
        for (auto &channel : _channels)
        {
            channel.Close();
            std::cout << "关闭：" << channel.Name() << std::endl;
        }
    }

    void WaitSubProcess()
    {
        for (auto &channel : _channels)
        {
            channel.Wait();
            std::cout << "回收：" << channel.Name() << std::endl;
        }
    }

private:
    std::vector<Channel> _channels;
    int _next; // 轮询发消息  序号
};

class ProcessPool
{
public:
    ProcessPool(int n) :_process_num(n)
    {
        _tm.Register(PrintLog);
        _tm.Register(Download);
        _tm.Register(Upload);
    }
    ~ProcessPool() {}

    void Work(int fd)
    {
        while (true)
        {
            int code = 0;
            ssize_t n = read(fd, &code, sizeof(code));
            if (n > 0)
            {
                if (n != sizeof(code))
                {
                    continue;
                }

                std::cout << "子进程：[" << getpid() << "]收到一个任务码" << code << std::endl;
                _tm.Execute(code);
            }

            else if (n == 0)
            {
                std::cout<<"子进程退出"<<std::endl;
                break;
            }

            else
            {
                std::cout<<"读取错误"<<std::endl;
                break;
            }
        }
    }

    void Run()
    {
        //选择一个任务
        int taskcode=_tm.Code();
        // 选择一个进程
        auto &process=_cm.Select();
        std::cout<<"选择了一个子进程"<<process.Name()<<std::endl;
        process.Send(taskcode);
        std::cout<<"选择了一个任务码"<<taskcode<<std::endl;

    }

    void Stop()
    {
        //关闭父进程的写端
        _cm.StopSubprocess();
        //回收
        _cm.WaitSubProcess();
    }

    void Debug()
    {
        _cm.PrintChannel();
    }

    bool Start()
    {
        for (int i = 0; i < _process_num; i++)
        {
            // 创建管道
            int fd[2] = {0};
            int n = pipe(fd);
            if (n < 0)
            {
                return false;
            }

            // 创建子进程
            pid_t subid = fork();
            if (subid < 0)
                return false;
            else if (subid == 0)
            {
                // 子进程  关闭不要的写端
                close(fd[1]);
                Work(fd[0]);
                close(fd[0]);
                exit(0);
            }

            else
            {
                // 父进程
                close(fd[0]);
                _cm.Insert(fd[1], subid);
            }
            
        }
        return true;
    }


private:
    ChannelManager _cm;
    int _process_num;
    TaskManager _tm;
};
#endif