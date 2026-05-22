//main.c

#include"proce.h"
double total=1024.0;
double speed=1.0;
int main()
{

    //process();
    double current=0;
    while(current<=total)
    {
         FlushProcess(total,current);
         usleep(3000);
         current+=speed;

    }
    printf("\n");
    printf("\ndownload %.2lfMB Done\n", current);
    return 0;
}
