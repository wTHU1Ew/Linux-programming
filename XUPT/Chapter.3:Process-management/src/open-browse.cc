#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char* argv[])
{
    pid_t pbrowse=fork();
    if(pbrowse==-1)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if(pbrowse==0)
    {
        char* const cmd[] = { "firefox", NULL };
        const char * firefox = "firefox";
        execvp(firefox, cmd);
        perror("execvp"); // 只有当 execvp 失败时才会执行到这里
        exit(EXIT_FAILURE);
    }
    else
    {
        pid_t rpid;
        int pstatus;
        while((rpid=waitpid(pbrowse,&pstatus, WNOHANG|WCONTINUED))>=0)
        {
            sleep(5);
            if (WIFEXITED(pstatus))
            {
                printf("Child process:%d exited with status %d\n", pbrowse, WEXITSTATUS(pstatus));
            }
            else if (WIFSIGNALED(pstatus))
            {
                printf("Child process:%d terminated by signal %d\n", pbrowse, WTERMSIG(pstatus));
            }
            else if (WIFSTOPPED(pstatus))
            {
                printf("Child process:%d stopped by signal %d\n", pbrowse, WSTOPSIG(pstatus));
            }
            else if (WIFCONTINUED(pstatus))
            {
                printf("Child process:%d continued\n", pbrowse);
            }
        }
        printf("finished~\n");
    }
    return 0;
}