#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[]) {
    printf("Chosen Environment variables:\n");

    for (int i = 0; envp[i] != NULL; ++i) {

        char cmd[50] = "";

        for (int c = 0; envp[i][c] != '='; ++c)
            cmd[c] = envp[i][c];

        for (int j = 0; j < argc; ++j) {
            if (!strcmp(argv[j], cmd)) printf("%s\n", envp[i]);
        }
    }
    return 0;
}

// check with printenv PATH HOME USERNAME (or any arguments)
// and echo $PATH (or any argument)

// You can create env variables with export $(NAME)=$(CONTENT) (ex: export DIR1=123-testing)