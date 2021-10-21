#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 2) {
        printf("Wrong number of arguments(2 or 3)");
        return 1;
    }

    FILE* file1 = fopen(argv[1], "r");
    FILE* file2;

    if (argc != 2) file2 = fopen(argv[2], "w");

    char buffer[256];
    
    int i = 0;
    char c;
    while (1) {
        c = fgetc(file1);
        if (feof(file1)) break;
        buffer[i++] = c;
    }

    if (argc == 2){
        printf("%s", buffer);
    } else{
        fwrite(buffer, 1, i, file2);
        fclose(file2);
    }

    fclose(file1);

    return 0;
}