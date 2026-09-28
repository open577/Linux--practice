#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int ticket = 100;
void *route(void *mes)
{
    char *id = (char *)mes;
    while (true)
    {
        pthread_mutex_lock(&lock);
        if (ticket > 0)
        {
            usleep(1000);
            printf("%s tickkts:%d\n", id, ticket);
            ticket--;
            pthread_mutex_unlock(&lock);
        }

        else
        {
            pthread_mutex_unlock(&lock);
            break;
        }
    }
    return nullptr;
}

int main()
{
    pthread_t t1, t2, t3, t4;

    pthread_create(&t1, NULL, route, (void *)"thread 1");
    pthread_create(&t2, NULL, route, (void *)"thread 2");
    pthread_create(&t3, NULL, route, (void *)"thread 3");
    pthread_create(&t4, NULL, route, (void *)"thread 4");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    return 0;
}