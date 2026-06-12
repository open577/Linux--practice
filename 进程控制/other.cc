#include <iostream>
#include <cstdio>
#include <unistd.h>

int main(int argc, char *argv[], char *env[])
{
    std::cout << "hello C++, My Pid Is: " << getpid() << std::endl;

    for(int i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    printf("\n");

    for(int i = 0; env[i]; i++)
    {
        printf("env[%d]: %s\n", i, env[i]);
    }

    return 0;
}
