#include <iostream>
#include <pthread.h>

namespace MutexModule
{
    class Mutex
    {
    public:
        Mutex()
        {
            pthread_mutex_init(&_mutex, nullptr);
        }

        void Lock()
        {
            pthread_mutex_lock(&_mutex);
        }

        void UnLock()
        {
            pthread_mutex_unlock(&_mutex);
        }

        ~Mutex()
        {
            pthread_mutex_destroy(&_mutex);
        }

    private:
        pthread_mutex_t _mutex;
    };

    class LockGrund
    {
    public:
        LockGrund(Mutex &mutex) : _mutex(mutex)
        {
            _mutex.Lock();
        }

        ~LockGrund()
        {
            _mutex.UnLock();
        }

    private:
        Mutex &_mutex;
    };
}
