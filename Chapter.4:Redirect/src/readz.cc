#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main()
{
    setbuf(stdin, 0);
    setbuf(stdout, 0);
    setbuf(stderr, 0);

    int rfd=open("./a.txt", O_RDONLY);
    char buffer[1024];
    memset(buffer, 0, 1024);
    int nread=read(rfd, buffer, 50);
    write(1, buffer, strlen(buffer));
    //fflush(stdout);
    printf("\n%d, %d\n", nread, strlen(buffer));
    /*
    for(auto i: buffer)
    {
        printf("%d\n", i);
    }
    */

    nread=read(rfd, buffer, 50);
    printf("\n%d, %d\n", nread, strlen(buffer));
    write(1, buffer, strlen(buffer));
    
    return 0;
}