// Turn off echoing on screen of keyboard characters: example program.

#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void getFromFiles(int argc, char *argv[]) {
    int fdin = open(argv[1], O_RDONLY);
    int fdout = STDIN_FILENO;
    if (argc > 2) {
        fdout = open(argv[2], O_WRONLY);
    }

    char c;
    do {
        if (read(fdin, &c, 1) != 1) break;
        c = toupper(c);
        write(fdout, &c, 1);
    } while (c != '\n');
}

int main(int argc, char *argv[]) {

    if (argc > 1) {
        getFromFiles(argc, argv);
        return 0;
    }

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
    } while (c != EOF);
    tcsetattr(STDIN_FILENO, TCSANOW, &tms_ini);	// reset configuration

	return 0;
}
