      	"li t0, 16\n\t"				
	"addi %[lw_cnt], %[lw_cnt], 1\n\t"	//count lw
	"KeepLooping:\n\t"
	"addi %[others_cnt], %[others_cnt], 1\n\t" //count others 
	"lw x18, (%[x])\n\t"
	"addi %[lw_cnt], %[lw_cnt], 1\n\t"
	"addi %[x], %[x], 2\n\t"
	"addi %[arith_cnt], %[arith_cnt], 1\n\t"
	"lw x19, (%[h])\n\t"
	"addi %[lw_cnt], %[lw_cnt], 1\n\t"
	"addi %[h], %[h], 2\n\t"
	"addi %[arith_cnt], %[arith_cnt], 1\n\t"
	"add x20, x18, x19\n\t"   		// add result to *p_y
	"addi %[arith_cnt], %[arith_cnt], 1\n\t" //count arthi 
	"sw x20, 0(%[y])\n\t"   		// store result to *p_y
	"addi %[sw_cnt], %[sw_cnt], 1\n\t" 	//count sw
        "addi %[y], %[y], 2\n\t"                //p_y ++
	"addi t0, t0, -1\n\t"
	"addi %[arith_cnt], %[arith_cnt], 2\n\t"
	"bnez t0, KeepLooping\n\t" 
