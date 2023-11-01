#include <stdio.h>
#include <stdlib.h>

const int BUFF_SIZE = 1024;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *src;
    FILE *dst;
    if ((src = fopen(argv[1], "rb")) == nullptr)
    {
        perror("src: fopen()");
        exit(EXIT_FAILURE);
    }

    if ((dst = fopen(argv[2], "wb")) == nullptr)
    {
        fclose(src);
        perror("dst: fopen()");
        exit(EXIT_FAILURE);
    }

    char buff[BUFF_SIZE];
    size_t readSize = 0;
    while ((readSize = fread(buff, 1, BUFF_SIZE, src)) > 0)
    {
        fwrite(buff, 1, BUFF_SIZE, dst);
    }

    fclose(src);
    fclose(dst);
    return 0;
}
