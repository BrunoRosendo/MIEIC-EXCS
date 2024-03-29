/*
*	Example of threads in action
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 3

void *rot(void* a) {
	int i = *((int*)a);
	int* exit = malloc(sizeof(int));
	*exit = i*i;
	printf("\n\t In thread PID: %d ; TID: %lu.", getpid(), (unsigned long) pthread_self());
	sleep(3);
	pthread_exit(((void*) exit));	// no termination code
	return (void*) exit;
}

int main() {
	int i;	// thread counter
	pthread_t ids[NTHREADS];	// storage of (system) Thread Identifiers

setbuf (stdout, NULL);	// only for debugging
printf("\nMain thread PID: %d ; TID: %lu.\n", getpid(), (unsigned long) pthread_self());

// new threads creation
for(i=0; i<NTHREADS; i++) {
	int* index = malloc(sizeof(int));
	*index = i;
	if (pthread_create(&ids[i], NULL, rot, (void*) index) != 0)
		exit(-1);	// here, we decided to end process
	else
		printf("\nNew thread %d ; TID: %lu.", i, (unsigned long) ids[i]);
	}
// wait for finishing of created threads
for(i=0; i<NTHREADS; i++) {
	void* exit;
	pthread_join(ids[i], &exit);	// Note: threads give no termination code
	printf("\nTermination of thread %d: %lu with exit status %d.", i, (unsigned long)ids[i], *((int*)exit));
}

printf("\n");
pthread_exit(NULL);	// here, not really necessary...
return 0;	// will not run this!
}

// See threads with ps --pid [PID] -T