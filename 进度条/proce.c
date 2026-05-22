//proce.c
#include"proce.h"
#include<stdio.h>
void process()
{
    char buffer[N];
    const char* stat="|/-\\";
    memset(buffer,0,sizeof(buffer));
    int len=strlen(stat);
    int count=0;
    while(count<=100)
    {
        double rate=count /(double)(N-1);
        printf("[%-100s][%d%%][%c]\r",buffer,(int)(rate*100),stat[count%len]);
        fflush(stdout);
        
        buffer[count]= STATE;
        count++;
        usleep(5000);
    }
    printf("\n");
}

void FlushProcess(double total, double current)
{
    char buffer[N];
    const char* stat="|/-\\";
    memset(buffer,0,sizeof(buffer));
    int len=strlen(stat);
    int num=(int)(current*100/total);
    static int cnt=0;
    for(int i=0;i<=num;i++)
        {
            buffer[i]=STATE;
        }
    double rate=current/total;
    cnt%=len;
    printf("[%-100s][%d%%][%c]\r",buffer,(int)(rate*100),stat[cnt]);
    cnt++;
    fflush(stdout);
}

