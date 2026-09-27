#include <iostream>
#include <string>
#include <functional>

namespace ThreadModlue
{
    static int number = 0;
    template <typename T>
    class Thread
    {
        void EnableDeteach()
        {
            std::cout << _name << "分离成功" << std::endl;
            _isdeteach = true;
        }

        void EnableRunning()
        {
            std::cout << _name << "正常运行" << std::endl;
        }

        using func_t = std::function<void(T)>;

    public:
        Thread(T data)
            :_tid(0),
            _isdeteach(false), _isrunning(false), _data(data)
        {
            _name = "thread-" + std::to_string(number++);
        }

        static void *routine(void *mes)
        {
            Thread<T> *self = static_cast<Thread<T> *>(mes);
            self->EnableRunning();
            if(self->_isdeteach)
            {
                self->Deteach();
            }
            // self->_func(self->_data);
            self->_data;
            return nullptr;
        }
        bool Start()
        {
            if (_isrunning)
                return false;

            int n = pthread_create(&_tid, nullptr, routine, this);
            if (n != 0)
            {
                std::cout << "线程创建失败" << std::endl;
                return false;
            }
            else
            {
                std::cout << "线程创建成功" << std::endl;
            }
            return true;
        }

        bool Join()
        {
            if (_isdeteach)
            {
                std::cout << "线程已经分离，不能join" << std::endl;
                return false;
            }

            int n = pthread_join(_tid, nullptr);
            if (n != 0)
            {
                std::cout << "join失败" << std::endl;
                return false;
            }
            return true;
        }

        bool Deteach()
        {
            if (_isdeteach)
            {
                return false;
            }

            int n = pthread_detach(_tid);
            if (n != 0)
            {
                std::cout << "分离失败" << std::endl;
                return false;
            }
            else
            {
                EnableDeteach();
                return true;
            }
        }

        bool Stop()
        {
            if (_isrunning)
            {
                int n = pthread_cancel(_tid);
                if (n != 0)
                {
                    std::cout << "暂停失败" << std::endl;
                    return false;
                }
                else
                {
                    _isrunning = false;
                    std::cout << _name << " stop" << std::endl;
                    return true;
                }
            }
            return false;
        }

    private:
        pthread_t _tid;
        std::string _name;
        bool _isdeteach;
        bool _isrunning;
        func_t _func;
        void *_res;
        T _data;
    };
}
