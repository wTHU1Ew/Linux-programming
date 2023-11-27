#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

const int FUNCTION_FAILED = -1;

int removeDirectory(const char *);

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        int result;
        int flagR = 0;
        while ((result = getopt(argc, argv, "r")) != -1)
        {
            switch (result)
            {
            case 'r':
                flagR = 1;
                break;
            default:
                break;
            }
        }

        for (int i = optind; i < argc; i++)
        {
            if (flagR)
            {
                if (removeDirectory(argv[i]))
                {
                    perror("removeDirectory()");
                }
            }
            else
            {
                if (unlink(argv[i]))
                {
                    perror("remove()");
                }
            }
        }
    }
    else
    {
        printf("Required one or two parameters.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int removeDirectory(const char *path)
{
    DIR *dirp;
    dirent *direntp;

    if ((dirp = opendir(path)) == nullptr)
    {
        perror("opendir()");
        return FUNCTION_FAILED;
    }

    while ((direntp = readdir(dirp)) != nullptr)
    {
        //printf("%s\n", direntp->d_name);
        if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
        {
            continue;
        }

        char fullpath[PATH_MAX];
        if (path[strlen(path) - 1] != '/')
        {
            snprintf(fullpath, sizeof(fullpath), "%s/%s", path, direntp->d_name);
            //printf("%s\n", fullpath);
        }
        else
        {
            snprintf(fullpath, sizeof(fullpath), "%s%s", path, direntp->d_name);
            //printf("%s\n", fullpath);
        }

        if (direntp->d_type == DT_DIR)
        {
            removeDirectory(fullpath);
        }
        else
        {
            if (unlink(fullpath))
            {
                perror("unlink()");
                return FUNCTION_FAILED;
            }
        }
    }

    if (rmdir(path))
    {
        perror("rmdir()");
        return FUNCTION_FAILED;
    }

    return 0;
}