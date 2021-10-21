/*
*	Example of signals in action (with SIGACTION)
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void func(int signo) {
	printf("World\n");
	exit(0);
}

void printChild() {
	printf("Hello ");
	exit(0);
}

int main()
{
	struct sigaction childNew, childOld;
	sigset_t childMask; // defines signals to block while func() is running

	if (sigemptyset(&childMask) == -1) // block no signal
		perror("sigsetfunctions");

	childNew.sa_handler = func;
	childNew.sa_mask = childMask;
	childNew.sa_flags = 0;

	if (sigaction(SIGCHLD, &childNew, &childOld))
		perror("sigaction");

	int id = fork();

	if (id)
	{
		//sleep(5);
		printf("Hello:\n");
		pause();
	}

	else
	{
		//sleep(2);
		printChild();
	}

	return 0;
}