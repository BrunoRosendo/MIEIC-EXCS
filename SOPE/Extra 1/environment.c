#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("USER=%s\n", getenv("USER_NAME"));
    return 0;
}