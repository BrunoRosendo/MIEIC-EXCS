#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

void bye(void)
{
    printf("\nThat was all, folks\n");
}

int main(void)
{
    signal(SIGINT, intHandler);
    while (keepRunning) {
        // just chilling
    }

    int i = atexit(bye);
    if (i != 0)
    {
        printf("cannot set exit function\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}