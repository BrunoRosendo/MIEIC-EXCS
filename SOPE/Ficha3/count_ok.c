/* Testing access issues to shared variables
 * - Race conditions!
 * JMMC - Out.2001
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXCOUNT 100000
long count;
void *thr_fun(void *);
int active_process = 0;
int nthreads;

int main(int argc, char *argv[]) {
	pthread_t *ptid;
	int i;

	setbuf(stdout, NULL);
	if (argc < 2) {
		printf("\nUsage: %s #threads\n", argv[0]);
		exit(1);
	}
	nthreads = atoi(argv[1]);
	ptid = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
	if (ptid == NULL) {
		perror("malloc");
		exit(2);
	}
	for (i = 0; i < nthreads; i++) {
		if (pthread_create(&ptid[i], NULL, thr_fun, i) != 0) {
			perror("pthread_create");
			exit(3);
		}
	}
	for (i = 0; i < nthreads; i++)
		pthread_join(ptid[i], NULL);

	printf("\nEND!\n");
	return 0;
}

void *thr_fun(void *arg) {
	while (count < MAXCOUNT) {
        if (active_process == arg) {
            printf("\n%ld", count);
            count++;
            active_process = (active_process + 1) % nthreads;
        }
	}
	printf("\nEND thread %lu!\n", (unsigned long)pthread_self());
	return (NULL);
}
