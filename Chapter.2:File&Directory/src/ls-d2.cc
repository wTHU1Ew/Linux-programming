#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

typedef int mode;

const int FUNC_FAILED = -1;
const int WRONG_ARGV = -2;

const mode F_SHOW = 1;
const mode F_LONG = 2;

void showHelp();
int showDirectory(const char *path, mode flag);
bool compareDirentp(const dirent *a, const dirent *b);

int main(int argc, char *argv[])
{
    mode flag = 0;
    char result;

    while ((result = char(getopt(argc, argv, "-alh"))) != -1)
    {
        switch (result)
        {
        case 'a':
            flag = flag | F_SHOW;
            break;
        case 'l':
            flag = flag | F_LONG;
            break;
        case 'h':
            showHelp();
            return 0;
        case '?':
            printf("Try 'ls -h' for more information.\n");
            exit(WRONG_ARGV);
        default:
            break;
        }
    }

    showDirectory("./", flag);

    return 0;
}

void showHelp()
{
    printf("Usage: ls [OPTION]... [FILE]...\nList information about the FILEs (the current directory by default).\n\n  -a, --all                  do not ignore entries starting with .\n  -l                         use a long listing format\n");
}

int showDirectory(const char *path, mode flag)
{
    DIR *dirp;
    dirent *direntp;
    struct stat *statp;
    std::vector<dirent *> vdirentp;

    if ((dirp = opendir(path)) == nullptr)
    {
        perror("opendir()");
        return FUNC_FAILED;
    }
    
    while ((direntp = readdir(dirp)) != nullptr)
    {
        if ((direntp->d_name)[0] == '.')
        {
            if ((flag & F_SHOW) == 0)
            {
                continue;
            }
        }
        vdirentp.push_back(direntp);
    }
    closedir(dirp);

    std::sort(vdirentp.begin(), vdirentp.end(), compareDirentp);
    

    if ((flag & F_LONG) != 0)
    {
        for(auto p:vdirentp)
        {
            lstat(p->d_name, statp);
            printf("%d\t%s\n", statp->st_mode,p->d_name);
        }
    }
    else
    
    {
        for (auto p : vdirentp)
            printf("%s\t", p->d_name);
    }

    printf("\n");

    return 0;
}

bool compareDirentp(const dirent *a, const dirent *b)
{
    return (strcmp(a->d_name, b->d_name) < 0);
}