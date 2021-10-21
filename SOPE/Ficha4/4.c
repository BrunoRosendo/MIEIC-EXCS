#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

int main() {
    while (1) {
        system("vmstat -a");
        char* p = (char*) malloc(50*pow(10, 6));  // 50 MB
        memset(p, 'A', 50*pow(10, 6));
        if (p == NULL) break;
        sleep(1);
    }
    return 0;
}

// https://www.thegeekstuff.com/2012/01/time-command-examples/
// Test with time utility aswell
// /usr/bin/time -f "\nsize: %D ; %K ; %X ; %p (Kilobytes)\npaging: %Z (bytes) ; %F ; %R ; %M ; %t (Kilobytes)\nswap: %W\n" ./4
