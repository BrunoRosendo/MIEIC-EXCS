#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define BUF_LENGTH 256
int main(int argc, char* argv[]) {
    printf("usage: errors %s, %s\n", argv[1], argv[2]);
    if (argc != 3) {
        printf("Wrong number of arguments\n");
        exit(3);
    }
    FILE *src, *dst;
    char buf[BUF_LENGTH];
    if (( src = fopen( argv[1], "r" )) == NULL ){
        printf("ERROR: %d", errno);
        exit(1);
    }
    if (( dst = fopen( argv[2], "w" )) == NULL ){
        printf("ERROR: %d", errno);
        exit(2);
    }
    while(( fgets( buf, BUF_LENGTH, src )) != NULL){
        fputs( buf, dst );
    }
    fclose( src );
    fclose( dst );
    exit(0);  // zero é geralmente indicativo de "sucesso" }
}