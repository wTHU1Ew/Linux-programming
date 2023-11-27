#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int tunnel[2];
    if (pipe(tunnel) == -1)
    {
        perror("pipe()");
        exit(EXIT_FAILURE);
    }
    pid_t bro1, bro2;
    if ((bro1 = fork()) == -1)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if (bro1 == 0)
    {
        const char *const demop = "process Bro1 is writing to process Bro2\n";
        close(tunnel[0]);
        write(tunnel[1], demop, strlen(demop));
        close(tunnel[1]);
        exit(0);
    }
    else
    {
        if ((bro2 = fork()) == -1)
        {
            perror("fork()");
            exit(EXIT_FAILURE);
        }
        else if(bro2==0)
        {
            char buff[1024];
            close(tunnel[1]);
            int nread;
            if((nread=read(tunnel[0], buff, sizeof(buff)))<0)
            {
                perror("read()");
                exit(EXIT_FAILURE);
            }
            close(tunnel[0]);
            write(1, buff, nread);
            exit(0);
        }
        else
        {
            int status1, status2;
            if(waitpid(bro1, &status1, 0)>0)
            {
                if(WIFEXITED(status1))
                {
                    printf("Child process %d exited with status %d\n", bro1, WEXITSTATUS(status1));
                }
                else
                {
                    printf("Child process %d did not exit normally\n", bro1);
                }
            }
            else
            {
                perror("waitpid()");
                return -1;
            }
            if(waitpid(bro2, &status2, 0)>0)
            {
                if(WIFEXITED(status2))
                {
                    printf("Child process %d exited with status %d\n", bro2,WEXITSTATUS(status2));
                }
                else
                {
                    printf("Child process %d did not exit normally\n", bro2);
                }
            }
            else
            {
                perror("waitpid()");
                return -1;
            }
            return 0;
        }
        return -1;
    }

    return -1;
}