/*
sum_col:
leaq   1(, %rdi, 4), %r8        # %r8 = 4 * n + 1
leaq   (%rdi, %rdi, 2), %rax    # result = 3 * n
movq   %rax, %rdi               # %rdi = 3 * n
testq  %rax, %rax
jle    .L4                      # if %rax <= 0, goto L4
salq   $3, %r8                   # %r8 = 8 * (4 * n + 1)
leaq   (%rsi, %rdx, 8), %rcx    # %rcx = A[0][j]的地址
movl   $0, %eax                 # result = 0
movl   $0, %edx                 # i = 0
.L3:
addq   (%rcx), %rax             # result += A[i][j]
addq   (, %rdx                 # i += 1
addq   %r8, %rcx                # 这里每次+8*(4n+1),说明每一行有4n+1个，因此NC(n)为4*n+1
cmpq   %rdi, %rdx               
jne    .L3                      # 当%rdx等于3*n才循环结束，所以可以说明一共有3n行，因此NR(n)为3*n
rep; ret
.L4:
movl $0, %eax
ret
*/
