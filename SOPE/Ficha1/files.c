#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]){
    chdir("/home/bruno/");
    if (argc != 2) {
        printf("Wrong number of arguments");
        return 1;
    }

    char input[100];
    strcpy(input, argv[1]);

    DIR* dir;
    struct dirent* file;
    dir = opendir(input);

    if (!dir){
        printf("Error opening directory");
        return 1;
    }
    
    unsigned num = 0;

    while ((file = readdir(dir)) != NULL){
        struct stat info;
        char path[100];
        strcpy(path, input);
        strcat(path, file->d_name);
        if (stat(path, &info) != 0){
            printf("err: %d\n", errno);
            continue;
        }
        if (S_ISREG(info.st_mode)) {
            printf("name: %s size: %ld\n", file->d_name, info.st_size);
            num++;
        }
    }

    closedir(dir);
    printf("Number of regular files: %d\n", num);
    return 0;
}

// check with ls [PATH] | wc -l