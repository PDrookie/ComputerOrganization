#include <stdio.h>
int main ()
{
int a[10] = {0}, b[10]= {0}, c[10] = {0};
int i, arr_size = 10;
FILE *input = fopen("../input/2.txt","r");
for(i = 0; i<arr_size; i++) fscanf(input, "%d", &a[i]);
for(i = 0; i<arr_size; i++) fscanf(input, "%d", &b[i]);
for(i = 0; i<arr_size; i++) fscanf(input, "%d", &c[i]);
fclose(input);
int *p_a = &a[0];
int *p_b = &b[0];
int *p_c = &c[0];
/* Original C code segment
for (int i = 0; i < arr_size; i++){
*p_c++ = *p_a++ / *p_b++;
}
*/
for (int i = 0; i < arr_size; i++){
    asm volatile(
        "lw t0, 0(%0)\n"   // load a[i] into t0
        "lw t1, 0(%1)\n"   // load b[i] into t1
        "div t2, t0, t1\n" // divide t0 by t1 and store the result in t2
        "sw t2, 0(%2)\n"   // store the result in c[i]
        "addi %0, %0, 4\n" // increment p_a by 4
        "addi %1, %1, 4\n" // increment p_b by 4
        "addi %2, %2, 4\n" // increment p_c by 4
        :
        : "r"(p_a), "r"(p_b), "r"(p_c)
        : "t0", "t1", "t2"
    );
}
p_c = &c[0];
for (int i = 0; i < arr_size; i++)
printf("%d ", *p_c++);
return 0;
}
