#include <limits.h>
/*
 * @note 计算 3 / 4 * x 
 *       不溢出则需要先进行除以 4 ，然后再乘以 3
 *
 *       假定 f 为 x 的高 30 位， l 为 x 的低 2 位 ，则有
 *       f = x & ~0x3
 *       l = x & 0x3
 *       x = f + l
 *       threeforths(x) = f/4*3 + l*3/4
 *       此时低位只需考虑舍入问题，高位只需考虑溢出问题       
 */

int threeforths(int x) {
    int is_neg = x & INT_MIN;
    int f = x & ~0x3;
    int l = x & 0x3;

    int fd4 = f >> 2;
    int fd4m3 = (fd4 << 1) + fd4;

    int lm3 = (l << 1) + l;
    int bias = (1 << 2) - 1;
    lm3 = is_neg ? lm3 + bias : lm3;
    int lm3d4 = lm3 >> 2;

    return fd4m3 + lm3d4;
}
