"li t1, 16\n\t"
"addi %[lw_cnt], %[lw_cnt], 1\n\t"
"vvaddint32:\n\t"
"vsetvli t0, t1, e32, ta, ma\n\t"
"addi %[others_cnt], %[others_cnt], 1\n\t"
"sub t1, t1, t0\n\t"
"slli t0, t0, 2\n\t"
"addi %[others_cnt], %[others_cnt], 1\n\t"
"vle32.v v0, (%[x])\n\t"
"add %[x], %[x], t0\n\t"
"addi %[arith_cnt], %[arith_cnt], 1\n\t"
"vle32.v v1, (%[h])\n\t"
"addi %[lw_cnt], %[lw_cnt], 2\n\t"
"add %[h], %[h], t0\n\t"
"vadd.vv v2, v0, v1\n\t"     
"vse32.v v2, (%[y])\n\t"
"addi %[sw_cnt], %[sw_cnt], 1\n\t"
"add %[y], %[y], t0\n\t"
"addi %[arith_cnt], %[arith_cnt], 5\n\t"
"bnez t1, vvaddint32\n\t"   