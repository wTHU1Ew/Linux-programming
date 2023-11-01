#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

const int BUFF_SIZE=0x10000;

int main(int argc, char* argv[])
{
        if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int fd=open(argv[1], O_RDONLY);
    char buff[BUFF_SIZE];
    int readSize=0;
    if((readSize=read(fd, buff,BUFF_SIZE))<=0)
    {
        perror("read()");
        exit(EXIT_FAILURE);
    }
    close(fd);
    if(write(1, buff, readSize)<=0)
        {
        perror("write()");
        exit(EXIT_FAILURE);
    }
    printf("\n");
    
    return 0;
}