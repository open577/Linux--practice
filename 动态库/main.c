#include "my_stdio.h"
#include "my_string.h"
#include <stdio.h>
int main()
{
const char *s = "abcdefg";
printf("%s: %d\n", s, my_strlen(s));
mFILE *fp = mfopen("./log.txt", "a");
if(fp == NULL) return 1;
mfwrite(s, my_strlen(s), fp);
mfwrite(s, my_strlen(s), fp);
mfwrite(s, my_strlen(s), fp);
mfclose(fp);
return 0;
}

