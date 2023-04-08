// description: matrix muliply without for loop
#include<stdio.h>
int main()
{
int i=0;
int h[9]={0}, x[3]={0}, y[3]={0};
FILE *input = fopen("../input/4.txt","r");
for(i = 0; i<9; i++) fscanf(input, "%d", &h[i]);
for(i = 0; i<3; i++) fscanf(input, "%d", &x[i]);
for(i = 0; i<3; i++) fscanf(input, "%d", &y[i]);
fclose(input);
int *p_x = &x[0] ;
int *p_h = &h[0] ;
int *p_y = &y[0] ;
asm volatile(
    "li t0, 0\n" // Initialize the output value to 0
    "li t1, 0\n" // Initialize the loop counter to 0
    "li t2, 0\n" // Initialize the row counter to 0
   
    "outer_loop:\n"
    "beq t2, 3, end_outer_loop\n" // Exit the loop when all rows have been processed
    "li t1, 0\n" // Reset the loop counter for each new row

    "inner_loop:\n"
    "beq t1, 3, end_inner_loop\n" // Exit the loop when all columns have been processed
    "slli t3, t1, 2\n" // Calculate the memory offset for the current column
    "add t3, t2, t3\n"
    "lw a0, %0(t3)\n" // Load the current value from matrix h
    "slli t3, t1, 2\n" // Calculate the memory offset for the current column of x
    "lw a1, %1(t3)\n" // Load the current value from matrix x
    "mul a0, a0, a1\n" // Multiply the values
    "add t0, t0, a0\n" // Accumulate the result
    "addi t1, t1, 1\n" // Increment the loop counter
    "j inner_loop\n" // Repeat the loop for the remaining columns

    "end_inner_loop:\n"
    "slli t3, t2, 2\n" // Calculate the memory offset for the current row of y
    "sw t0, %2(t3)\n" // Store the accumulated result in the output matrix
    "addi t2, t2, 1\n" // Increment the row counter
    "j outer_loop\n" // Repeat the loop for the remaining rows

    "end_outer_loop:\n"
    :
    : "r" (p_h), "r" (p_x), "r" (p_y)
    : "a0", "a1", "t0", "t1", "t2", "t3"
);
p_y = &y[0];
for(i = 0; i<3; i++)
printf("%d \n", *p_y++);
return(0) ;
}

