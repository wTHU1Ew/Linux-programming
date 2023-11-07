#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

typedef int fd;

const int BUFFSIZE = 1024;

int main(int argc, char *argv[])
{
    fd pass = open("./pass", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (pass == -1)
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    fd passwd = open("/etc/passwd", O_RDONLY);
    if (passwd == -1)
    {
        close(pass);
        perror("open()");
        exit(EXIT_FAILURE);
    }

    char buff[BUFFSIZE];
    size_t nread;

    while ((nread = read(passwd, buff, sizeof(buff))) > 0)
    {
        if ((write(pass, buff, nread)) != nread)
        {
            close(pass);
            close(passwd);
            perror("write()");
            exit(EXIT_FAILURE);
        }
    }

    close(pass);
    close(passwd);
    return 0;
}