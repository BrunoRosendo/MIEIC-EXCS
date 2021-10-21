#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>

void printFiles(char filePath[]) {
    DIR* dir;
    struct dirent* file;
    dir = opendir(filePath);

    if (!dir){
        printf("Error opening directory");
        exit(1);
    }
    
    unsigned num = 0;

    while ((file = readdir(dir)) != NULL){
        struct stat info;
        char* path;
        path = realpath(filePath, NULL);
        if (strcmp(file->d_name, ".") == 0 ||
            strcmp(file->d_name, "..") == 0)
                continue;
        strcat(path, "/");
        strcat(path, file->d_name);
        printf("%s\n", path);
        if (lstat(path, &info) != 0){
            printf("err: %d\n", errno);
            continue;
        }
        if (S_ISREG(info.st_mode)) {
            printf("name: %s size: %ld\n", file->d_name, info.st_size);
            num++;
        }
        else if (S_ISDIR(info.st_mode)) {
            int id = fork();
            switch (id)
            {
            case 0:
                printFiles(path);
                exit(0);
                break;
            
            default:
                wait(0);
                break;
            }
        }
    }

    closedir(dir);
    printf("Number of regular files: %d\n", num);
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Wrong number of arguments");
        return 1;
    }

    char input[100];
    strcpy(input, argv[1]);
    printFiles(input);
    return 0;
}

// check with ls [PATH] | wc -l