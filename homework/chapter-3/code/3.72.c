/*
----------


----------      <-- %rbp  0


---------- s1     <-- -16
e1
----------
p
---------- p
e2
---------- s2


A:
    s1 分配了 16 字节的空间给 i 和 p 。并分配了 8n+30 的栈空间，利用掩码使 rsp 向下舍入到最近的 16 倍数, 保证栈帧对齐 16 字节
    这里的-16的十六进制表示为0xfffffff0，之所以用& 就是为了求16的整数倍

B:
    p = (s2 + 15) & 0xfffffff0
    使 rsp 向上舍入到最近的 16 倍数地址

C:
    s2 = s1 - (0xfffffff0 & (8n + 30)) 根据这个公式, 由于是舍入到最近的 16 倍数，
    当 n 是偶数的时候，我们可以把式子简化为 s2 = s1 - (8 * n + 16)
    当 n 是奇数的时候，我们可以把式子简化为 s2 = s1 - (8 * n + 24)

    先求 e1 最小的情况:
    e1 和 e2 是对立的关系，要想 e1 最小，那么 e2 就要最大，考虑到对齐 16 字节，e2 最大也就是 15 ，
    其次要让 s2 最小 , 可以让空闲的空间达到最小, 即 16 个字节 ，n 为偶数时 s2 最小, e1 = 16 - 15 = 1 

    e1 最大的情况, 此时需要让 s2 最大, e2 最小，即 e2 == 0 ，n 为奇数，故 e1 == 24 。

D:
    s2 确保栈帧对齐 16 字节， p 能够保证自身的首地址为 16 对齐

*/
