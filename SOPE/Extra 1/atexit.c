#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void first() {
    printf("Executing exit handler 1\n");
}

void second() {
    printf("Executing exit handler 2\n");
}

int main() {
    int v1, v2;
    v1 = atexit(first);
    v2 = atexit(second);
    if (v1 != 0 || v2 != 0){
        printf("atexit() registration failed\n");
        exit(1);
    }
    printf("Main done!\n");
    return 0;
}