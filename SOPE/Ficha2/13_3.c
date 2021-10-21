#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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
        char msg[256];
        read(pp[0], msg, 256);
        strcat(msg, " Systems");
        printf("%s\n", msg);
        close(pp[0]);

        write(pp[1], "Systems", 1+strlen("Systems"));
        close(pp[1]);
    } else {
        write(pp[1], "Operating", 1 + strlen("Operating"));
        close(pp[1]);
        int wstatus;
        wait(&wstatus);

        char msg[256];
        read(pp[0], msg, 256);
        char msg2[256] = "Operating ";
        strcat(msg2, msg);
        printf("%s\n", msg2);
        close(pp[0]);
    }

    return 0;
}