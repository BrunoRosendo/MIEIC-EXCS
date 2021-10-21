#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int proc;
    int np;

    if (mkfifo("/tmp/np2", 0666) < 0) {
        perror("mkfifo()");
        exit(1);
    }
    if ((proc = fork()) == -1) {
        perror("fork()");
        exit(2);
    }
    if (proc == 0) {
        char msg[256];
        while ((np = open("/tmp/np", O_RDWR)) < 0) ; // sync
        read(np, msg, 256);
        strcat(msg, " Systems");
        printf("%s\n", msg);

        write(np, "Systems", 1+strlen("Systems"));
        close(np);
    } else {
        while ((np = open("/tmp/np", O_RDWR)) < 0) ; // sync
        write(np, "Operating", 1 + strlen("Operating"));
        int wstatus;
        wait(&wstatus);

        char msg[256];
        read(np, msg, 256);
        char msg2[256] = "Operating ";
        strcat(msg2, msg);
        printf("%s\n", msg2);
        close(np);
    }

    return 0;
}