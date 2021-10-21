#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 2

void *rot(void* a) {
	printf("%s", (char*) a);
    return NULL;
}

int main() {
    pthread_t ids[NTHREADS];

    for(int i=0; i<NTHREADS; i++) {
        char * string = (char*) malloc(10);
        if (i == 0) string = "Operating ";
        else string = "Systems\n";
        if (pthread_create(&ids[i], NULL, rot, (void*) string) != 0)
            exit(-1);	// here, we decided to end process
	}

    for(int i=0; i<NTHREADS; i++)
        pthread_join(ids[i], NULL);	// Note: threads give no termination code

    return 0;
}