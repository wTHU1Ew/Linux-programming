#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int fd;

const char *filep = "./pass";
const int BUFFSIZE = 1024;
const int FUNC_FAILED = -1;

fd createFile();

int main(int argc, char *argv[])
{
    fd pass = open(filep, O_RDWR | O_TRUNC);
    if (pass == -1)
    {
        pass = createFile();
    }
    if (pass == -1)
    {
        perror("createFile()");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "1") == 0)
    {
        struct flock f1;
        f1.l_type = F_RDLCK;
        f1.l_whence = SEEK_SET;
        f1.l_start = 0;
        f1.l_len = 0;
        if (fcntl(pass, F_SETLK, &f1) == -1)
        {
            perror("fcntl()");
            close(pass);
            exit(EXIT_FAILURE);
        }

        printf("Read lock acquired. Press Enter to release...\n");
        getchar();

        f1.l_type = F_UNLCK;
        if (fcntl(pass, F_SETLK, &f1) == -1)
        {
            perror("fcntl()");
            close(pass);
            exit(EXIT_FAILURE);
        }
    }
    else if (strcmp(argv[1], "2") == 0)
    {
        struct flock f2;
        f2.l_type = F_WRLCK;
        f2.l_whence = SEEK_SET;
        f2.l_start = 0;
        f2.l_len = 0;
        if (fcntl(pass, F_SETLK, &f2) == -1)
        {
            perror("fcntl()");
            close(pass);
            exit(EXIT_FAILURE);
        }

        printf("Write lock acquired. Press Enter to release...\n");
        getchar();

        f2.l_type = F_UNLCK;
        if (fcntl(pass, F_SETLK, &f2) == -1)
        {
            perror("fcntl()");
            close(pass);
            exit(EXIT_FAILURE);
        }
    }
    close(pass);
    return 0;
}

fd createFile()
{
    fd pass = open(filep, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (pass == -1)
    {
        perror("open()");
        return FUNC_FAILED;
    }

    fd passwd = open("/etc/passwd", O_RDONLY);
    if (passwd == -1)
    {
        close(pass);
        perror("open()");
        return FUNC_FAILED;
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
            return FUNC_FAILED;
        }
    }

    close(passwd);
    return pass;
}