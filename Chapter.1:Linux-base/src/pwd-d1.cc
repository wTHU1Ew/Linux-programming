#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *cwd;
    cwd = getcwd(NULL, 0);
    if (cwd != NULL) {
        printf("%s\n", cwd);
        free(cwd);
    } else {
        perror("getcwd");
        return 1;
    }

    return 0;
}
