#ifndef __LOG_HPP__
#define __LOG_HPP__
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <ctime>
#include "Mutex.hpp"
using namespace MutexModule;

namespace LogMoudle
{
    const std::string step = "\r\n";
    class LogStrategy
    {
    public:
        ~LogStrategy() = default;
        virtual void SyncLog(const std::string &message) = 0;
    };

    // 显示器刷新策略
    class ConsoleLogStrategy : public LogStrategy
    {
    public:
        ConsoleLogStrategy() {}
        void SyncLog(const std::string &message)
        {
            LockGrund lock(_mutex);
            std::cout << message << step;
        }

    private:
        Mutex _mutex;
    };

    const std::string defaultpath = "./mylog";
    const std::string defaultfile = "log";

    class FileLogStrategy : public LogStrategy
    {
    public:
        FileLogStrategy(std::string path = defaultpath, std::string file = defaultfile)
            : _path(path), _file(file)
        {
            LockGrund lock(_mutex);
            if (std::filesystem::exists(_path))
            {
                return;
            }
            try
            {
                std::filesystem::create_directories(_path);
            }

            catch (const std::filesystem::filesystem_error &e)
            {
                std::cerr << e.what() << step;
            }
        }

        void SyncLog(const std::string &message)
        {
            LockGrund lock(_mutex);

            std::string filename = _path + (_path.back() == '/' ? "" : "/") + _file;
            std::ofstream out(filename, std::ios::app);
            if (!out.is_open())
            {
                return;
            }

            out << message << step;
            out.close();
        }

    private:
        std::string _path;
        std::string _file;

        Mutex _mutex;
    };

    enum class LogLevel
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    std::string Level2str(LogLevel level)
    {
        switch (level)
        {

        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
        }
    }
    std::string GetTimeStamp() 
    {
        char buffer[128];
        time_t tm=time(nullptr);
        struct tm curr_tm;
        localtime_r(&tm,&curr_tm);
        snprintf(buffer,sizeof(buffer),"%4d-%02d-%02d %02d:%02d:%02d",
        curr_tm.tm_year+1900,
            curr_tm.tm_mon+1,
            curr_tm.tm_mday,
            curr_tm.tm_hour,
            curr_tm.tm_min,
            curr_tm.tm_sec
        );
        return buffer;
    }
    class Logger
    {
    public:
        void EnableFileLogStrategy()
        {
            _fflush_strategy = std::make_unique<FileLogStrategy>();
        }

        void EnableConsoleLogStrategy()
        {
            _fflush_strategy = std::make_unique<ConsoleLogStrategy>();
        }

        Logger()
        {
            EnableConsoleLogStrategy();
        }
        class LogMessage
        {
        public:
            LogMessage(LogLevel &level, std::string src_file, int line_number, Logger &logger)
                : _time(GetTimeStamp()), _level(level), _pid(getpid()), _src_file(src_file), _line_number(line_number), _logger(logger)
            {
                std::stringstream ss;
                ss << "[" << _time << "]" << " "
                   << "[" << Level2str(level) << "]" << " "
                   << "[" << _pid << "]" << " "
                   << "[" << _src_file << "]" << " "
                   << "[" << _line_number << "]" << " ";

                _info = ss.str();
            }

            template <typename T>
            LogMessage &operator<<(const T &info)
            {
                std::stringstream ss;
                ss << info;
                _info += ss.str();
                return *this;
            }

            ~LogMessage()
            {
                //_fflush_strategy->SyncLog(_info);
                if (_logger._fflush_strategy)
                {
                    _logger._fflush_strategy->SyncLog(_info);
                }
            }

        private:
            std::string _time;
            LogLevel _level;
            pid_t _pid;
            std::string _src_file;
            int _line_number;
            std::string _info;
            Logger &_logger;
        };
        LogMessage operator()(LogLevel level, std::string name, int line)
        {
            return LogMessage(level, name, line, *this);
        }

    private:
        std::unique_ptr<LogStrategy> _fflush_strategy;
    };
    Logger logger;
    // 使用宏，简化用户操作，获取文件名和行号
    #define LOG(level) logger(level, __FILE__, __LINE__)
    #define Enable_Console_Log_Strategy() logger.EnableConsoleLogStrategy()
    #define Enable_File_Log_Strategy() logger.EnableFileLogStrategy()

}

#endif
