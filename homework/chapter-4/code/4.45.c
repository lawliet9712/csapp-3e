1. 没有，如果 REG 是 %rsp ，会把 %rsp - 8 的值 push 到栈上
2. movq REG, -8(%rsp)
   subq $8, %rsp
