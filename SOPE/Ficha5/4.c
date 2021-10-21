#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main() {
    printf("clock ticks per second: %lu\n", sysconf(_SC_CLK_TCK));

    time_t stamp = 0;
    printf("%s", ctime(&stamp));

    struct timeval val;
    printf("Size: %lu bytes\n", sizeof(val));

    return 0;
}
