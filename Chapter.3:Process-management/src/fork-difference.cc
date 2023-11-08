#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

const int times = 5;

int main(int argc, char *argv[])
{
    int a = 1, b = 10;
    int c = 1, d = 10;
    printf("\nthis is fork():\n");
    pid_t p1 = fork();

    if (p1 == -1)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if (p1 == 0)
    {
        for (int t = 0; t < times; t++)
        {
            sleep(1);
            a++, b++;
            printf("child: a=%d, b=%d\n", a, b);
        }
        printf("!!!child: a+b= %d!!!\n", (a + b));
        exit(0);
    }
    else
    {
        for (int t = 0; t < times; t++)
        {
            sleep(1);
            a++, b++;
            printf("parent: a=%d, b=%d\n", a, b);
        }
        printf("!!!parent: a+b= %d!!!\n", (a + b));
    }

    sleep(6);

    printf("\nthis is vfork():\n");
    pid_t p2 = vfork();
    if (p1 == -1)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if (p2 == 0)
    {
        for (int t = 0; t < times; t++)
        {
            sleep(1);
            c++, d++;
            printf("c=%d, d=%d\n", c, d);
        }
        printf("!!!child: c+d= %d!!!\n", (c + d));
        exit(0);
    }
    else
    {
        for (int t = 0; t < times; t++)
        {
            sleep(1);
            c++, d++;
            printf("c=%d, d=%d\n", c, d);
        }
        printf("!!!parent: c+d= %d!!!\n", (c + d));
    }
    
    
    return 0;
}