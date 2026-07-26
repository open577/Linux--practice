#include "my_stdio.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
mFILE *mfopen(const char *filename, const char *mode)
{
int fd = -1;
if(strcmp(mode, "r") == 0)
{
fd = open(filename, O_RDONLY);
}
else if(strcmp(mode, "w")== 0)
{
fd = open(filename, O_CREAT|O_WRONLY|O_TRUNC, 0666);
}
else if(strcmp(mode, "a") == 0)
{
fd = open(filename, O_CREAT|O_WRONLY|O_APPEND, 0666);
}
if(fd < 0) return NULL;
mFILE *mf = (mFILE*)malloc(sizeof(mFILE));
if(!mf)
{
close(fd);
return NULL;
}
mf->fileno = fd;
mf->flag = FLUSH_LINE;
mf->size = 0;
mf->cap = SIZE;
return mf;
}
void mfflush(mFILE *stream)
{
if(stream->size > 0)
{
// 写到内核⽂件的⽂件缓冲区中!
write(stream->fileno, stream->outbuffer, stream->size);
// 刷新到外设
fsync(stream->fileno);
stream->size = 0;
}
}
int mfwrite(const void *ptr, int num, mFILE *stream)
{
// 1. 拷⻉
memcpy(stream->outbuffer+stream->size, ptr, num);
stream->size += num;
// 2. 检测是否要刷新
if(stream->flag == FLUSH_LINE && stream->size > 0 && stream->outbuffer[stream->size-1]== '\n')
{
mfflush(stream);
}
return num;
}
void mfclose(mFILE *stream)
{
if(stream->size > 0)
{
mfflush(stream);
}
close(stream->fileno);
}

