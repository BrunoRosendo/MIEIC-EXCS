#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
       #include <sys/stat.h>

int main(int argc, char* argv[]) {
    printf("%s\n", argv[1]);
    DIR* dir = opendir(argv[1]);

    int max = 0;
    int min = -1;
    int totalSize = 0;
    int numFiles = 0;
    int sizes[500];
    int classFiles = 0;
    int blockSize = 0;
    int i = 0;

    struct dirent* file;
    while ((file = readdir(dir)) != NULL) {
        if (file->d_type != DT_REG) continue;
        struct stat fileStats;
        stat(file->d_name, &fileStats);

        numFiles++;

        off_t size = fileStats.st_size;
        if (size > max) max = size;
        if (size < min || min == -1) min = size;
        totalSize += size;
        sizes[i++] = size;

        mode_t mode = fileStats.st_mode;
        if (mode & 0x0444 || mode & 0x0666 || mode & 0x0111) classFiles++;

        if (blockSize == 0) blockSize = fileStats.st_blksize;
        // recursion missing, idc
    }
    printf("Smallest: %dB, Largest: %dB\n", min, max);
    printf("Average: %d, Median: %d\n", totalSize / numFiles, sizes[numFiles / 2]);
    printf("Number of files in the classes: %d\n", classFiles);
    printf("Total: %d\n", numFiles);
    printf("Block size: %dB\n", blockSize);
}
