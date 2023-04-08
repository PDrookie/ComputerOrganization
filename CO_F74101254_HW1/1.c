#include <stdio.h>

int main()
{
    int a, b;
    FILE *input = fopen("../input/1.txt", "r");
    fscanf(input, "%d %d", &a, &b);
    fclose(input);

    asm volatile(
        "lw a0, 0(sp)\n"    // Load a from stack pointer
        "lw a1, 4(sp)\n"    // Load b from stack pointer
        "div a0, a0, a1\n"  // Divide a by b and store result in a0
        "sw a0, 0(sp)\n"    // Store the result back to stack pointer
        "jr ra\n"           // Jump to the return address
    );

    printf("%d\n", a);

    return 0;
}
