#include <sys/signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void showtime(int sig);

int main()
{

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        struct sigaction action, oldaction;
        action.sa_handler = showtime;
        if (sigaction(SIGUSR1, &action, &oldaction) != 0)
        {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
        while (1)
        {
            pause();
        }
        exit(0);
    }
    else
    {
        char flag;
        pid_t waitp;
        while (1)
        {
            if ((waitp = waitpid(pid, NULL, WNOHANG | WCONTINUED)) >= 0)
            {
                scanf("%c", &flag);
                if (flag == '1')
                {
                    kill(pid, SIGUSR1);
                }
            }
        }
    }
}

void showtime(int sig)
{
    printf("signal mask is: %d\n\n", sig);
    struct tm *local_time;
    time_t t;

    t = time(NULL);
    local_time = localtime(&t);

    char strtime[100];
    memset(strtime, 0, sizeof(strtime));
    strftime(strtime, sizeof(strtime), "%Y-%m-%d: %H:%M:%S", local_time);
    printf("%s\n", strtime);
}