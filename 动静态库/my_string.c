#include "my_string.h"
int my_strlen(const char *s)
{
const char *end = s;
while(*end != '\0')end++;
return end - s;
}

