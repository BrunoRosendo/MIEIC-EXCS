#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments!");
        return 1;
    }
    int f = open(argv[1], O_RDONLY);

    if (f < 0) perror("Opening failed");
    else printf("Opening succeeded\n");

    return 0;
}

// Test with ./open Ficha-1.tx > ofile 2> efile