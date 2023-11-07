#include <stdio.h>
#include <stdlib.h>

const int BUFFSIZE = 1024;

int main(int argc, char *argv[])
{
    FILE *pass = fopen("./pass", "w+");
    if (pass == nullptr)
    {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    FILE *passwd = fopen("/etc/passwd", "r");
    if (pass == nullptr)
    {
        perror("fopen()");
        fclose(pass);
        exit(EXIT_FAILURE);
    }

    size_t nread;
    char buff[BUFFSIZE]={0};
    while((nread=fread(buff,1,BUFFSIZE,passwd))>0)
    {
        if(fwrite(buff, 1, nread, pass)!=nread)
        {
            perror("fwrite()");
            fclose(pass);
            fclose(passwd);
            exit(EXIT_FAILURE);
        }
    }

    fclose(pass);
    fclose(passwd);
    return 0;
}