#include <stdio.h>
int Sum(int s, int e)
{
    int result = 0;
    for(int i = s; i <= e; i++)
    {
        result += i;
    }
    return result;
}

int main()
{
    int start = 1;
    int end = 100;
    printf("I will begin\n");
    int n = Sum(start, end);
    printf("running done, result is: [%d-%d]=%d\n", start, end, n);
    return 0;
}

