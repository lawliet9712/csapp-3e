/*
store_prod:
movq   %rdx, %rax   # %rax = y
cqto                # convert q to o,4字符号拓展到8字,假如y的符号位为1,那么%rdx所有位都是1(此时值是-1),否则,%rdx全为0(此时值是0).%rdx = yh
movq   %rsi, %rcx   # %rcx = x
sarq   $63,  %rcx   # 将%rcx向右移63位,跟%rdx的含义一样,二进制位要么全是1,要么是0,%rcx = xh.
imulq  %rax, %rcx   # %rcx = y * xh
imulq  %rsi, %rdx   # %rdx = x * yh
addq   %rdx, %rcx   # %rcx = y * xh + x * yh,计算了第二项
mulq   %rsi         # 无符号计算 xl*yl,并将xl*yl的128位结果的高位放在%rdx,低位放在%rax,计算了第三项.
addq   %rcx, %rdx   # 将第二项计算结果加到%rdx
movq   %rax, (%rdi) # 将%rax的值放到dest的低位
movq   %rdx, 8(%rdi)# 将%rdx的值放到dest的高位
ret
*/

// 根据 x = 2^64 * xh + xl 和 y = 2^64 * yh + yl 可以得出 x * y = xh * yh * 2^128 + (xh * yl + xl * yh)* 2^64 + xlyl ，第一项左移128位会溢出，故舍去

