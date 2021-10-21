#include <stdio.h>

int main() {
    for (int i = 0; i < 100000; ++i)
        printf("Hello World!");
    printf("\n");
    return 0;
}

// Run with sudo time ./thousands