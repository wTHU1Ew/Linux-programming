#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t p = fork();
    if (p == -1)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if (p == 0)
    {
        printf("This is _exit.");
        printf("This is child process.");
        _exit(0);
    }
    else
    {
        printf("This is exit.");
        printf("This is parent process.");
        exit(0);
    }
}