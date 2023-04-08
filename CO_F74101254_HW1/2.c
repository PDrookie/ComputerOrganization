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
for (int i = 0; i < arr_size; i++)
asm volatile(
  "li t0, 10 \n"   // load array size
  "li t1, 0 \n"    // set loop counter to 0
  "la t2, a \n"    // load address of array a
  "la t3, b \n"    // load address of array b
  "la t4, c \n"    // load address of array c
  "loop: \n"
  "lw t5, 0(t2) \n" // load a[i] to t5
  "lw t6, 0(t3) \n" // load b[i] to t6
  "div t7, t5, t6 \n" // calculate a[i] / b[i]
  "sw t7, 0(t4) \n" // store result to c[i]
  "addi t1, t1, 1 \n" // increment loop counter
  "addi t2, t2, 4 \n" // increment pointer for array a
  "addi t3, t3, 4 \n" // increment pointer for array b
  "addi t4, t4, 4 \n" // increment pointer for array c
  "bne t1, t0, loop \n" // loop until all elements are processed
);
p_c = &c[0];
for (int i = 0; i < arr_size; i++)
printf("%d ", *p_c++);
return 0;
}
