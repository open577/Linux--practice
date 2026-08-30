#pragma once

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH "."
#define FILENAME "fifo"

#define PER_EXIT(n)         \
    do                      \
    {                       \
        perror(n);          \
        exit(EXIT_FAILURE); \
    } while (true)

// 服务端
class NameFifo
{
public:
    NameFifo(const std::string &pash, const std::string &name)
        : _pash(pash), _name(name)
    {
        _fifoname = _pash + "/" + _name;
        // 创建管道
        unlink(_fifoname.c_str());
        umask(0);
        int n = mkfifo(_fifoname.c_str(), 0666);
        if (n < 0)
        {
            // 失败
            PER_EXIT("mkfifo");
        }

        else
        std::cout << "mkfifo success!" << std::endl;
    }

    ~NameFifo()
    {
        int n = unlink(_fifoname.c_str());
        if (n < 0)
        {
            // 失败
            PER_EXIT("unlink");
        }

        std::cout << "close success!" << std::endl;
    }

private:
    std::string _pash;
    std::string _name;
    std::string _fifoname;
};

// 客户端
class FileOper
{
public:
    FileOper(const std::string &pash, const std::string &name)
        : _pash(pash), _name(name), _fd(-1)
    {
        _fifoname = _pash + "/" + _name;
    }

    ~FileOper()
    {
        // int n = unlink(_fifoname.c_str());
        // if (n < 0)
        // {
        //     // 失败
        //     PER_EXIT("unlink");
        // }

        // std::cout << "close success!" << std::endl;
    }

    void OpenForRead()
    {
        _fd = open(_fifoname.c_str(), O_RDONLY);
        if (_fd < 0)
        {
            PER_EXIT("open");
        }

        std::cout << "open success!" << std::endl;
    }

    void OpenForWrite()
    {
        _fd = open(_fifoname.c_str(), O_WRONLY);
        if (_fd < 0)
        {
            PER_EXIT("open");
        }

        std::cout << "open success!" << std::endl;
    }

    void Read()
    {
        while (true)
        {
            char buffer[1024];
            ssize_t num = read(_fd, buffer, sizeof(buffer) - 1);
            if (num > 0)
            {
                buffer[num] = 0;
                std::cout << "Client says:" << buffer << std::endl;
            }
            else if (num == 0)
            {
                std::cout << "Client exit!" << std::endl;
                break;
            }

            else
            {
                perror("read file!\n");
                break;
            }
        }
    }

    void Write()
    {
        std::string message;
        int cnt = 1;
        pid_t id = getpid();

        while (true)
        {
            std::cout << "Please Enter:";
            std::getline(std::cin, message);
            message+= (", message number: " + std::to_string(cnt++) + ", [" + std::to_string(id) + "]");
            write(_fd,message.c_str(),message.size());
        }
    }
    void Close()
    {
        if(_fd>0)
        close(_fd);
    }

private:
    std::string _pash;
    std::string _name;
    std::string _fifoname;
    int _fd;
};