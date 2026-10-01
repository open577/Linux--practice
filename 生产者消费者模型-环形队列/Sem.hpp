#include <iostream>
#include<semaphore.h>


static const int NUM=1;

class SemModule
{
    public:
    SemModule(int defaultnum=NUM)
    {
        sem_init(&_sem,0,defaultnum);
    }

    void P()
    {
        sem_wait(&_sem);
    }

    void V()
    {
        sem_post(&_sem);
    }
    ~SemModule()
    {
        sem_destroy(&_sem);
    }
private:
    sem_t _sem;
};