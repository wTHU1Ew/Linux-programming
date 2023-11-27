#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        printf("%s\n", argv[1]);
        if (chdir(argv[1]) != 0)
        {
            perror("chdir()");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        const char *homeDirectory = getenv("HOME");
        if (homeDirectory == NULL)
        {
            fprintf(stderr, "HOME environment variable is not set.\n");
            exit(EXIT_FAILURE);
        }

        if (chdir(homeDirectory) != 0)
        {
            perror("chdir()");
            exit(EXIT_FAILURE);
        }
    }

    char currentDir[1024];
    if (getcwd(currentDir, sizeof(currentDir)) != NULL)
    {
        printf("Current working directory: %s\n", currentDir);
    }
    else
    {
        perror("getcwd()");
        exit(EXIT_FAILURE);
    }

    return 0;
}