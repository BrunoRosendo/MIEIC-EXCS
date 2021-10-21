#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong number of arguments(3)");
        return 1;
    }

    int file1 = open(argv[1], O_RDONLY);
    int file2 = open(argv[2], O_WRONLY | O_CREAT);

    char buffer[256];
    
    int i = 0;
    char c;
    while (read(file1, &c, 1) == 1)
        buffer[i++] = c;

    write(file2, buffer, i);
    close(file1);
    close(file2);

    return 0;
}