#include <stdio.h>

#define ONE_FLAG (1<<0) // 0000 0000 0000...0000 0001
#define TWO_FLAG (1<<1) // 0000 0000 0000...0000 0010
#define THREE_FLAG (1<<2) // 0000 0000 0000...0000 0100
#define FOUR_FLAG (1<<3) // 0000 0000 0000...0000 1000

void Print(int flags)
{
    if(flags & ONE_FLAG)
    {
        printf("One!\n");
    }
    if(flags & TWO_FLAG)
    {
        printf("Two\n");
    }
    if(flags & THREE_FLAG)
    {
        printf("Three\n");
    }
    if(flags & FOUR_FLAG)
    {
        printf("Four\n");
    }
}


int main()
{
    Print(ONE_FLAG);
    printf("\n");
    Print(ONE_FLAG | TWO_FLAG);
    printf("\n");
    Print(ONE_FLAG | TWO_FLAG | THREE_FLAG);
    printf("\n");
    Print(ONE_FLAG | TWO_FLAG | THREE_FLAG | FOUR_FLAG);
    printf("\n");
    Print(ONE_FLAG | FOUR_FLAG);
    printf("\n");
    return 0;
}
