#include "ProcessPool.hpp"

int main()
{
    ProcessPool pool(5);
    pool.Start();
    // pool.Debug();
    int cnt=10;
    while(cnt--)
    {
        pool.Run();
        sleep(1);
    }

    pool.Stop();
    return 0;
}