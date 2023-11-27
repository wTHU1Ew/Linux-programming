#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const int BUFFER_SIZE=1024;

int main(int argc, char* argv[])
{
    int rfd=open("./tmpfifo", O_RDONLY);
    char buffer[BUFFER_SIZE];
    int nread=0;
    memset(buffer, 0, BUFFER_SIZE);
    if(rfd<0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    while ((nread=read(rfd, buffer, BUFFER_SIZE))>0)
    {
        write(1, buffer, nread);
    }
    printf("\n");
    return 0;

}