#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong number of arguments\n");
        return 1;
    }

    srand(time(NULL));
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    int random = rand() % n1;
    int i = 1;
    while (random != n2) {
        printf("Iter %d: %d\n", i, random);
        random = rand() % n1;
        ++i;
    }
    printf("Finally got it!\n");

    return 0;
}

// user time ./random