#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    DIR *dirp;
    dirent *direntp;
    if ((dirp = opendir(".")) == nullptr)
    {
        perror("opendir()");
        exit(EXIT_FAILURE);
    }
    while ((direntp = readdir(dirp)) != nullptr)
    {
        if(direntp->d_name[0]=='.')
            continue;
        printf("%s\t", direntp->d_name);
    }
    printf("\n");
    closedir(dirp);
    return 0;
}