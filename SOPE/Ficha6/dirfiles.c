/* dirfiles.c
 * list a directory's regular files
 * jmcruz@fe.up.pt, 01.apr.2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char * argv[]) {
	char *dirname;
	char filename[1024] = {'\0'};
	DIR * od;
	struct dirent * ds;
	struct stat st;
if (argc < 2) {
	fprintf(stderr, "\n\tUsage: %s <dirname>\n", argv[0]);
	return (-1);
}
dirname = argv[1];
if ((od = opendir(dirname)) == NULL) {
	perror("opendir");
	exit(1);
}
while((ds = readdir(od)) != NULL) {
	if (!strcmp(ds->d_name, ".") || !strcmp(ds->d_name, ".."))
		continue;
	sprintf(filename, "%s/%s", dirname, ds->d_name);
	if (stat(filename, &st) < 0) {
		perror("stat");
		continue;
	}
	if ((st.st_mode & S_IFMT) == S_IFREG)
		printf("%s\n",  ds->d_name);
}
exit(0);
} // main()
