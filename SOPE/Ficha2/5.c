#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

    int id = fork();
    switch(id) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            printf("Hello ");
            break;
        default:{
            int wstatus;
            printf("World:\n");
            wait(&wstatus); // wait for all child processes
            printf("World!\n");
        }
    }

    return 0;
}