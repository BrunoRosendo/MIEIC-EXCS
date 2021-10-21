#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void funcInt(int signo) {
    printf("I died pid:%d\n", getpid()); // all processes receive them
    exit(1);
}

void funcUser(int signo) {
    printf("User signal id:%d\n", getpid()); // other processes don't receive them
}

int main() {
    int id1 = fork(); // parent
    if (!id1) {
        int id2 = fork(); // child
        if (!id2) {
            int id3 = fork(); // granchild
        }
    }

    // signals
    struct sigaction new, old;
	sigset_t smask;

    if (sigemptyset(&smask) == -1) // block no signal
        perror("sigsetfunctions");
    new.sa_handler = funcInt;
    new.sa_mask = smask;
    new.sa_flags = 0;

    if(sigaction(SIGINT, &new, &old) == -1)
	    perror ("sigaction");

    struct sigaction new2, old2;
	sigset_t smask2;

    if (sigemptyset(&smask2) == -1) // block no signal
        perror("sigsetfunctions");
    new2.sa_handler = funcUser;
    new2.sa_mask = smask2;
    new2.sa_flags = 0;

    if(sigaction(SIGUSR1, &new2, &old2) == -1)
	    perror ("sigaction");
    sleep(30);

    return 0;
}

// group leader has the same PID and PGID. Session leader has the same sid, pgid and pid
