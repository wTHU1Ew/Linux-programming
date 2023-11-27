#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t zombie = fork();
    if (zombie == -1)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if (zombie == 0)
    {
        printf("process %d will be a zombie!\n", getpid());
        exit(0);
    }
    else
    {
        pid_t orphan = fork();
        if (orphan == -1)
        {
            perror("fork()");
            exit(EXIT_FAILURE);
        }
        else if (orphan == 0)
        {
            while(1)
            {
                sleep(3);
                printf("process %d is orphan!\n", getpid());
                printf("parent: %d.\n", getppid());
            }
        }
        else
        {
            sleep(20);
            printf("parent process %d is dead.\n", getpid());
            return 0;
        }
    }
}