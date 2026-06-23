#include"mystdio.h"
#include<string.h>
#include<unistd.h>
int main()
{
    Mfile *filep=MFopen("log.txt","w");
    //const char *msg="hello myfile\n";
    //int size=MWrite(fp,void(msg),strlen(msg));
    //FClose(fp);

    int cnt = 10;
    while(cnt--)
    {
        char *msg = (char*)"hello myfile!!!";
        MWrite(filep, msg, strlen(msg));
        printf("buffer: %s\n", filep->outbuffer);
        
        MFlush(filep);
        sleep(1);
    }
    MClose(filep); // FILE *fp
    return 0;
}
