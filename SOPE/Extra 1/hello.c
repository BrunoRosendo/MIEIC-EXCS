#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Wrong number of arguments\n");
        return 1;
    }
    int num = atoi(argv[1]);
    for (int j = 0; j < num; ++j){
        printf("Hello");
        for (int i = 2; i < argc; ++i) {
            printf(" %s", argv[i]);
        }
        printf("!\n");
    }
    return 20;
}