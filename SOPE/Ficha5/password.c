// Turn off echoing on screen of keyboard characters: example program.

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    printf("Insert your username: ");
    char name[100];
    scanf("%s", name);

    printf("Insert your password:");
    fflush(STDIN_FILENO);

	char pass[100];
    char c;
	struct termios tms, tms_ini;

	tcgetattr(STDIN_FILENO, &tms_ini); // read console's configuration
	tms = tms_ini;

	tms.c_lflag &= ~ (ECHO | ICANON | ECHOE | ECHOK | ECHONL); // inhibit char echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &tms); // set new configuration
	while (1) {
		if (read(STDIN_FILENO, &c, 1) != 1)
			perror("read failed");
        if (c == '\n') break;
        if (c == '\b') pass[strlen(pass) - 1] = '\0';

        strncat(pass, &c, 1);
        printf("***");
        fflush(STDIN_FILENO);
	}

    tcsetattr(STDIN_FILENO, TCSANOW, &tms_ini);	// reset configuration
    printf("\n%s %s\n", name, pass);

	return 0;
}
