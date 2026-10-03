#include <iostream>
#include <vector>
#include <pthread.h>
#include <mutex>
#include <queue>

int clientnum = 5;
namespace BlockQueue
{
    template <class T>
    class Block
    {
    private:
        bool IsEmpty()
        {
            return _q.empty();
        }

        bool Isfull()
        {
            return _q.size() >= _cap;
        }

    public:
        Block()
        {
            _c_wait=0;
            _p_wait=0;
            _cap = clientnum;
            pthread_mutex_init(&_block, nullptr);
            pthread_cond_init(&_empty_cond, nullptr);
            pthread_cond_init(&_full_cond, nullptr);
        }

        void Push(const T in)
        {
            pthread_mutex_lock(&_block);

            while(Isfull())
            {
                _p_wait++;
                pthread_cond_wait(&_full_cond, &_block);
                _p_wait--;
            }

            _q.push(in);

            if (_c_wait > 0)
            {
                pthread_cond_signal(&_empty_cond);
                std::cout << "唤醒客户端" << std::endl;
            }

            pthread_mutex_unlock(&_block);
        }

        T Pop()
        {
            pthread_mutex_lock(&_block);

            while(IsEmpty())
            {
                _c_wait++;
                pthread_cond_wait(&_empty_cond, &_block);
                _c_wait--;
            }

            T data = _q.front();
            _q.pop();

            if (_p_wait > 0)
            {
                pthread_cond_signal(&_full_cond);
                std::cout << "唤醒服务端" << std::endl;
            }

            pthread_mutex_unlock(&_block);

            return data;
        }
        ~Block()
        {
            _cap = 0;
            pthread_mutex_destroy(&_block);
            pthread_cond_destroy(&_empty_cond);
            pthread_cond_destroy(&_full_cond);
        }

    private:
        std::queue<T> _q;
        int _cap;
        pthread_mutex_t _block;
        pthread_cond_t _empty_cond;
        pthread_cond_t _full_cond;

        int _c_wait;
        int _p_wait;
    };
}