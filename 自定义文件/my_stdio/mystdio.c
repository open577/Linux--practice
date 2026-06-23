#include"mystdio.h"
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
void MFlush(Mfile *stream)
{
    if(stream->bufferlen<0) return;
    int n=write(stream->fd,stream->outbuffer,stream->bufferlen);
    //void(n);
    fsync(stream->fd);
    stream->bufferlen = 0;
}

Mfile *BuyFile(int ffd,int fflag)
{
    Mfile *myfile=(Mfile*)malloc(sizeof(Mfile));
    myfile->fd=ffd;
    myfile->flag=fflag;
    myfile->bufferlen=0;
    myfile->flush_method=LINE_FLUSH;
    memset(myfile->outbuffer,0,sizeof(myfile->outbuffer));
    return myfile;
}

Mfile* MFopen(const char *path,const char *mode)
{
    int fd=-1;
    int flag=0;
    if(strcmp(mode,"w")==0)
    {
        flag=O_CREAT | O_WRONLY | O_TRUNC;
        fd=open(path,flag,0666);
    }

    else if(strcmp(mode,"a")==0)
    {
        flag=O_CREAT | O_WRONLY | O_APPEND;
        fd=open(path,flag,0666);
    }

    else if(strcmp(mode,"r")==0)
    {
        flag=O_RDWR;
        int fd=open(path,0);
    }

    else 
    {
        //TODO
    }

    if(fd==-1) return NULL;
    return BuyFile(fd,flag);
}


int MWrite(Mfile *file,void *msg,int len)
{
    memcpy(file->outbuffer+file->bufferlen,msg,len);

    file->bufferlen+=len;
    //file->outbuffer[file->bufferlen]='\0';
    if((file->flush_method & LINE_FLUSH) && file->outbuffer[file->bufferlen-1] == '\n')
    MFlush(file);
    return 0;
}

void MClose(Mfile *stream)
{
    MFlush(stream);
    close(stream->fd);
    free(stream);
}

