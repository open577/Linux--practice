#include<iostream>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>


using namespace std;

//C语言
//int main()
//{
//
//    FILE *fp=fopen("myfile","w");
//    if(fp==NULL)
//    {
//        perror("file error\n");
//        exit(1);
//    }
//    const char *msg="hello linux\n";
//    int count=4;
//    while(count--)
//    fwrite(msg,strlen(msg),1,fp);
//    fclose(fp);
//    return 0;
//}
//

//int main()
//{
//
//    int fd=open("myfile1",O_CREAT|O_WRONLY,0666);
//    if(fd<0)
//    {
//        perror("file error\n");
//        exit(1);
//    }
//    const char *msg="hello linux\n";
//    int count=4;
//    while(count--)
//    write(fd,msg,strlen(msg));
//    close(fd);
//    return 0;
//}
//
int main(int argc,char *argv[])
{

    if(argc==2)
    {
        int fd=open(argv[1],O_RDONLY);
        if(fd>0)
        dup2(fd,0);
        
        char buffer[1024];
        if((read(fd,buffer,sizeof(buffer)-1)>0))
                {

                    printf("%s\n",buffer);
                }
    }
    return 0;
}

//int main()
//{
//
//    //printf("hello\n");
//    //fprintf(stdout,"hello\n");
//
//    const char *msg="hello\n";
//    int count =5;
//    while(count--)
//    write(1,msg,strlen(msg));
//    //fflush(stdout);
//    return 0;
//}
//

//int main()
//{
//    int fd=open("myfile",O_WRONLY|O_APPEND);
//    const char *msg="hello wyy\n";
//    if(fd<0) perror("open fail\n");
//    write(fd,msg,strlen(msg));
//    return 0;
//}
//



//int main()
//{
//    int fd=open("myfile",O_RDONLY);
//    if(fd<0) 
//    {
//        perror("open fail\n");
//        exit(1);
//    }
//    char buffer[1024];
//    memset(buffer,0,sizeof(buffer));
//    int size=0;
//    while(( size = read(fd, buffer,sizeof(buffer)-1)) > 0)
//    {
//
//        if(size>0)
//        {
//            buffer[size]='\0';
//            printf("%s\n",buffer);
//        }
//
//        else if(size==0)
//        {
//            printf("文件读取完毕\n");
//        }
//
//        else
//            perror("read file\n");
//    }
//    close(fd);
//    return 0;
//}
