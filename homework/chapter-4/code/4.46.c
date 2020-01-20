1. 没有，如果 REG 是 %rsp ，会把 (%rsp) 的值 pop 到 %rsp 上而不是 %rsp + 8 上
2. addq $8, %rsp
   movq -8(%rsp), REG
