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
    "li x18, 0\n" 					// Initialize the loop counter to 0
    "outer_loop:\n\t"
    "	li x19, 0\n" 					// Initialize the row counter to 0 
    "	bge x18, %[max], end_outer_loop\n\t" 		// Exit the loop when all rows have been processed
    "	li x22, 0\n"					// Initialize the output to 0 
    "	add %[x], x0, %[Xi]\n\t"			// x[i]
    "inner_loop:\n\t"
    "	lw x20, 0(%[h])\n\t"				// load *p_h 
    "	lw x21, 0(%[x])\n\t"				// load *p_x
    "	mul x20, x20, x21\n\t"				// multiply	
    "	add x22, x22, x20\n\t"   			// add the result to p_y    
    "	addi %[h], %[h], 4\n\t"			// p_h ++
    "	addi %[x], %[x], 4\n\t"			// p_x ++
    "	addi x19, x19, 1\n\t"				// row couter ++
    "	bge x19, %[max], end_inner_loop\n" 		// Exit the loop when all columns have been processed
    "	beq x0, x0, inner_loop\n\t" 			// keep doing the inner loop 
    "end_inner_loop:\n"
    "	sw x22, 0(%[y])\n\t" 				// Store the result in the output matrix
    "	addi %[y], %[y], 4\n\t"				// p_y ++
    "	addi x18, x18, 1\n\t" 				// Increment the loop counter
    "	beq x0, x0, outer_loop\n\t"			// run the outer_loop	
    "end_outer_loop:\n\t"
    : [h] "+r" (p_h), [x] "+r" (p_x), [y] "+r" (p_y)
    : [max] "r"(3), [Xi] "r"(&x[0])
    : "x18", "x19", "x20", "x21", "x22"
);
p_y = &y[0];
for(i = 0; i<3; i++)
printf("%d \n", *p_y++);
return(0) ;
}
