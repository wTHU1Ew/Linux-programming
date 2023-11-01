#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        mode_t m = 0775;
        if (remove(argv[1]))
        {
            perror("remove()");
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