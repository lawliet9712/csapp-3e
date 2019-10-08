// 假定有二维数组 D[S][T]，那么 D[i][j] 的地址为 T * i + j ，假定有三维数组 D[R][S][T] ， 那么 D[i][j][k] 的任意元素地址公式为 ST * i + T * j + k 。 

/*
store_ele:
leaq  (%rsi, %rsi, 2), %rax  # %rax = 3 * j
leaq  (%rsi, %rax, 4), %rax  # %rax = j + 4(3j) = 13 * j
leaq  %rdi, %rsi             # %rsi = i
salq  $6, %rsi               # %rsi * = 64
addq  %rsi, %rdi             # %rdi = 65 * i
addq  %rax, %rdi             # %rdi = 65 * i + 13 * j
addq  %rdi, %rdx             # %rdx = 65 * i + 13 * j + k
movq  A(, %rdx, 8), %rax     # %rax = A + 8 * (65 * i + 13 * j + k)
movq  %rax, (%rcx)           # *dest = A[65 * i + 13 * j + k]
movl  $3640, %eax            # sizeof(A) = 3640
ret
*/

// S * T = 65
// T = 13
// S * T * R * 8 = 3640
// R = 7 ; s = 5 ; T = 13 
