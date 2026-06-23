#pragma once

#include <stdio.h>

#define MAX 1024
#define NONE_FLUSH (1<<0)
#define LINE_FLUSH (1<<1)
#define FULL_FLUSH (1<<2)

typedef struct IO_FILE
{
    int fd;
    int flag;
    char outbuffer[MAX];
    int bufferlen;
    int flush_method;
}Mfile;


Mfile *BuyFile(int ffd,int fflag);
Mfile *MFopen(const char *path,const char *mode);
int MWrite(Mfile *, void *str, int len);
void MFlush(Mfile *stream);
void MClose(Mfile *stream);

