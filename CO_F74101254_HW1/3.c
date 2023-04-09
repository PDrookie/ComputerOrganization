#include<stdio.h>
int main()
{
	int f,i=0;
	int h[9]={0}, x[3]={0}, y[3]={0};
	FILE *input = fopen("../input/3.txt","r");
	for(i = 0; i<9; i++) fscanf(input, "%d", &h[i]);
	for(i = 0; i<3; i++) fscanf(input, "%d", &x[i]);
	for(i = 0; i<3; i++) fscanf(input, "%d", &y[i]);
	fclose(input);
	int *p_x = &x[0] ;
	int *p_h = &h[0] ;
	int *p_y = &y[0] ;
	for (i = 0 ; i < 3; i++)
	{
	p_x = &x[0] ;
	for (f = 0 ; f < 3; f++){
           asm volatile(
                "lw x18, 0(%[x])\n\t"   	// load *p_h 
                "lw x19, 0(%[h])\n\t"  	// load *p_x               
                "lw x20, 0(%[y])\n\t"		// load *p_y
                "mul x18, x18, x19\n\t"   	// multiply
                "add x20, x20, x18\n\t"   	// add result to *p_y
                "sw x20, 0(%[y])\n\t"   	// store result to *p_y
                "addi %[x], %[x], 4\n\t"	//p_x ++
                "addi %[h], %[h], 4\n\t"	//p_h ++
                "beq %[f], %[max], KeepLooping\n\t"	//check the loop
                "beq x0, x0, End\n\t" 	
                "KeepLooping:\n\t"
                "	addi %[y], %[y], 4\n\t"
                "End:\n\t"
                : [x] "+r"(p_x), [h]"+r"(p_h), [y]"+r"(p_y)
                : [f] "r"(f), [max] "r"(2)
                : "x18", "x19", "x20"
            );
	}
	}
	p_y = &y[0];
	for(i = 0; i<3; i++)
		printf("%d \n", *p_y++);
	return(0) ;
}
