#pragma once
#include <iostream>
#include <pthread.h>

// namespace MutexModule
// {
//     class Mutex
//     {
//     public:
//         Mutex()
//         {
//             pthread_mutex_init(&_mutex, nullptr);
//         }

//         void Lock()
//         {
//             int n=pthread_mutex_lock(&_mutex);
//             (void)n;
//         }

//         void UnLock()
//         {
//            int n= pthread_mutex_unlock(&_mutex);
//             (void)n;
//         }

//         ~Mutex()
//         {
//             pthread_mutex_destroy(&_mutex);
//         }

//         pthread_mutex_t *Get()
//         {
//             return &_mutex;
//         }

//     private:
//         pthread_mutex_t _mutex;
//     };

//     class LockGrund
//     {
//     public:
//         LockGrund(Mutex &mutex) : _mutex(mutex)
//         {
//             _mutex.Lock();
//         }

//         ~LockGrund()
//         {
//             _mutex.UnLock();
//         }

//     private:
//         Mutex &_mutex;
//     };
// }

#pragma once
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
            int n = pthread_mutex_lock(&_mutex);
            (void)n;
        }
        void Unlock()
        {
            int n = pthread_mutex_unlock(&_mutex);
            (void)n;
        }
        ~Mutex()
        {
            pthread_mutex_destroy(&_mutex);
        }
        pthread_mutex_t *Get()
        {
            return &_mutex;
        }
    private:
        pthread_mutex_t _mutex;
    };

    class LockGuard
    {
    public:
        LockGuard(Mutex &mutex):_mutex(mutex)
        {
            _mutex.Lock();
        }
        ~LockGuard()
        {
            _mutex.Unlock();
        }
    private:
        Mutex &_mutex;
    };
}
