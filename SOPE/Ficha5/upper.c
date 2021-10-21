// Turn off echoing on screen of keyboard characters: example program.

#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char c;
	struct termios tms, tms_ini;

    tcgetattr(STDIN_FILENO, &tms_ini); // read console's configuration
	tms = tms_ini;

	tms.c_lflag &= ~ (ECHO | ICANON | ECHOE | ECHOK | ECHONL); // inhibit char echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &tms); // set new configuration

    do {
		if (read(STDIN_FILENO, &c, 1) != 1)
			perror("read failed");

        printf("%c", toupper(c));
        fflush(STDIN_FILENO);
    } while (c != '\n');
    tcsetattr(STDIN_FILENO, TCSANOW, &tms_ini);	// reset configuration

	return 0;
}
