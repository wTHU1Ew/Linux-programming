#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    setbuf(stdin, NULL);
    setbuf(stdout,NULL);
    setbuf(stderr, NULL);
    if(mkfifo("./tmpfifo", 0644)!=0)
    {
        perror("mkfifo()");
    }
    int wfd=open("./tmpfifo",O_WRONLY);
    int nwrite=write(wfd, argv[1], strlen(argv[1]));
    if(nwrite!=strlen(argv[1]))
    {
        perror("write");
        exit(EXIT_FAILURE);
    }
    close(wfd);
    return 0;
}