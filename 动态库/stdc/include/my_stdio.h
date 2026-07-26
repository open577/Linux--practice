#pragma once
#define SIZE 1024
#define FLUSH_NONE 0
#define FLUSH_LINE 1
#define FLUSH_FULL 2
struct IO_FILE
{
int flag; // 
 
int fileno; // 
char outbuffer[SIZE];
int cap;
int size;
// TODO
};
typedef struct IO_FILE mFILE;
mFILE *mfopen(const char *filename, const char *mode);
int mfwrite(const void *ptr, int num, mFILE *stream);
void mfflush(mFILE *stream);
void mfclose(mFILE *stream);
