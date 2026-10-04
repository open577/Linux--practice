#include "Log.hpp"
#include <memory>
using namespace LogMoudle;

int main()
{
    Enable_Console_Log_Strategy();
    LOG(LogLevel::DEBUG) << "hello world" << 3.141;
    LOG(LogLevel::DEBUG) << "hello world" << 3.142;

    Enable_File_Log_Strategy();
    LOG(LogLevel::DEBUG) << "hello world" << 3.143;
    LOG(LogLevel::DEBUG) << "hello world" << 3.144;


    // std::unique_ptr<LogStrategy> strategy=std::make_unique<ConsoleLogStrategy>();
    // strategy->SyncLog("hello world");
    // std::unique_ptr<LogStrategy> strategy=std::make_unique<FileLogStrategy>();
    // strategy->SyncLog("hello world");

    // LogMessage(LogLevel::WARNING,"main.cc",12)<<"kk";
    // LogMessage("WARNNING","main.cc",12)<<"kk,"<< 3.14 << " " << 8899 << "aaaa";;

    //logger(LogMoudle::LogLevel::DEBUG, "main.cc", 10)<<"hhkj"<<5465;

    return 0;
}