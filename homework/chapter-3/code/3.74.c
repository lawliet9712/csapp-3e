/*
find_range:
vxorps %xmm1, %xmm1, %xmm1 // 清零
movq $0, %r8
movq $1, %r9
movq $2, %r10
movq $3, %rax
vucomiss %xmm1, %xmm0   // 进行比较，然后调用条件传送指令
cmovb %r8, %rax
cmove %r9, %rax
cmova %r10, %rax
ret
 */
