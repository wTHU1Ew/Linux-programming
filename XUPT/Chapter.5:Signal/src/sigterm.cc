#include <sys/signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    kill(atoi(argv[1]),SIGTERM);
    return 0;
}