/*
find_range:
vxorps %xmm1, %xmm1, %xmm1  //清零
vucomiss %xmm1, %xmm0       // 进行比较
jp .L1
ja .L2
jb .L3
je .L4
.L2:
movl $2, %eax
ret
.L3:
movl $0, %eax
ret
.L4:
movl $1, %eax
ret
.L1:
movl $3 %eax
rep; ret
 */
