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
			"lw a0, %0\n\t"    // load *p_h to a0
        		"lw a1, %1\n\t"    // load *p_x to a1
			"mul a0, a0, a1\n\t"   // multiply
			"lw a2, %2\n\t"    // load *p_y to a2
        		"add a2, a2, a0\n\t"   // add result to *p_y
        		"sw a2, %2\n\t"    // store result to *p_y
        		:
        		: "m"(*p_h), "m"(*p_x), "m"(*p_y)
        		: "a0", "a1", "a2"
        	);
      		p_h++;
        	p_x++;	
	}
	p_y++;
	}
	p_y = &y[0];
	for(i = 0; i<3; i++)
		printf("%d \n", *p_y++);
	return(0) ;
}
