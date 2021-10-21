#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

long int get_page_size(void)
{
    long int n;
    char *p;
    int u;
    for (n = 1; n; n *= 2) {
        p = mmap(0, n * 2, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (p == MAP_FAILED)
            return -1;
        u = munmap(p + n, n);
        munmap(p, n * 2);
        if (!u)  // if not failed, a new page has started in p + n
            return n;
    }
    return -1;
}

int main() {
    printf("Real page size = %ld\n", sysconf(_SC_PAGESIZE));

    FILE* meminfo, *vmstat;
    meminfo = fopen("/proc/meminfo", "r");
    vmstat = fopen("/proc/vmstat", "r");

    char name[50];
    while (strcmp(name, "Mapped:")) {
        fscanf(meminfo, "%s", name);
    }

    long int mapped;
    fscanf(meminfo, "%ld", &mapped);
    mapped *= 1000;
    fclose(meminfo);

    while (strcmp(name, "nr_mapped")) {
        fscanf(vmstat, "%s", name);
    }

    long int nr_mapped;
    fscanf(vmstat, "%ld", &nr_mapped);
    fclose(vmstat);
    printf("%ld %ld\n", mapped, nr_mapped);
    long int pageSize = mapped / nr_mapped;

    printf("Experimental page size 1 = %ld\n", pageSize);
    printf("Experimental page size 2 = %ld\n", get_page_size());
    return 0;
}