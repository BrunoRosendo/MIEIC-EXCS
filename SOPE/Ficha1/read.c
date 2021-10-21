#include <unistd.h>
#include <stdio.h>

int main() {
    char a[4];
    read(1, a, 0);
    return 0;
}

// Inspect disassembled code with objdump -d read.o
// static linking needs -static flag