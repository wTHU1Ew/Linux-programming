#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

const int BUFFSIZE = 1024;

int main(int argc, char *argv[])
{
    FILE *rptr = nullptr;
    FILE *wptr = nullptr;
    char buff[BUFFSIZE];
    int nread;
    if ((rptr = popen("cat file_example", "r")) == nullptr)
    {

        perror("popen()");
        exit(EXIT_FAILURE);
    }

    if ((wptr = popen("grep root", "w")) == nullptr)
    {
        pclose(rptr);
        perror("popen()");
        exit(EXIT_FAILURE);
    }

    while ((nread = read(fileno(rptr), buff, BUFFSIZE)) > 0)
    {
        write(fileno(wptr), buff, nread);
    }

    pclose(rptr);
    pclose(wptr);
    return 0;
}