#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int proc;
    int pp[2];

    if (pipe(pp) == -1) {
        perror("pipe()");
        exit(1);
    }
    if ((proc = fork()) == -1) {
        perror("fork()");
        exit(2);
    }
    if (proc == 0) {
        close(pp[1]);
        char msg[256];
        read(pp[0], msg, 256);
        strcat(msg, " Systems");
        printf("%s\n", msg);
    } else {
        close(pp[0]);
        write(pp[1], "Operating", 1 + strlen("Operating"));
    }

    return 0;
}