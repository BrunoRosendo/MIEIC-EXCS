#include <stdio.h>

int global;

int func(int i) {
    if (i >= 10) return i;
    i *= 2;
    printf("Recursive var: 0x%x\n", &i);
    return func(i);
}

void mallocfunc() {
    int* i = (int*) malloc(100);
    printf("Malloc var: 0x%x\n", i);
}

int main() {
    static int i = 100;
    printf("Func 1: 0x%x\n", func);
    printf("Func 2: 0x%x\n", mallocfunc);
    printf("Uninitialized global var: 0x%x\n", &global);
    printf("Initialized global var: 0x%x\n", &i);
    mallocfunc();
    func(2);
    return 0;
}
