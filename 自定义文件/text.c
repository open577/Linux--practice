#include<stdio.h>
#include <unistd.h>
#include<string.h>
int main()
{
    printf("hello printf\n");
    fprintf(stdout,"hello fprintf\n");
    const char *msg="hello fwrite\n";
    fwrite(msg,strlen(msg),1,stdout);

    const char *ss="hello write\n";
    write(1,ss,strlen(ss));

    fork();
    close(1);
    return 0;
}
