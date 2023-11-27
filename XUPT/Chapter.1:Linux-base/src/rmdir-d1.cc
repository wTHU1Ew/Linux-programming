#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc>=2)
    {
        if(rmdir(argv[1]))
        {
            perror("mkdir()");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Required a parameter.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}