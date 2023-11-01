#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc==3)
    {
        if(rename(argv[1], argv[2]))
        {
            perror("rename()");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Require two parameters.\n");
    }
    return 0;
}