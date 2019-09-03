#include <stdio.h>
#include <assert.h>

/*
 * 我们首先考虑作为浮点数f能表示的最大的合法的整数是多少？
 * V = M * 2^E E = e - bias 由这两个公式可知E越大越好也就是e越大越好
 * e ==> 11111110 不能是11111111，
 * 我们再考虑一个范围 0 <= f < 1 如果f在这个范围中，那么它的值就直接取0
 *  我们要找出这个范围的浮点位模式，0：0 00000000 00000000000000000000000
 * 1：0 01111111 00000000000000000000000
 * 在上边的这个空间的值直接取0就行
 * 那么f能表示的最大的合法的规格数是 0 11111110 111111111111111111111111
 * 超过这个数的就成为越界了
 * 如果在这个范围内：
 * E = exp - bias;
 * 我们知道M的值的二进制小数是1.xxxxx... 但是下边M的值明显是做了<<23操作的，因此后边就要用E- 23
 * M = frac | 0x800000;
 * f = M * 2^E 根据这个公式，向0取整
 * if (E > 23) {
 * num = M << (E - 23);
 * } else {
 * num = M >> (23 - E);
 * }
 **/


/*
 * * Compute (float) f
 * * If conversion cause overflow or f is NaN, return 0x80000000
 * */
typedef unsigned float_bits;

int float_f2i(float_bits f) {
    unsigned sig = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned bias = 0x7F;

    int num;
    unsigned E;
    unsigned M;

    // 先考虑阶码值过大和过小的情况
    if (exp >= 0 && exp < 0 + bias) {
        /* number less than 1 */
        num = 0;
    } else if (exp >= 31 + bias) {
        /* number overflow */
        /* or f < 0 and (int)f == INT_MIN */
        num = 0x80000000;
    } else {
        E = exp - bias;
        M = frac | 0x800000;

        // 当 E 大于 23 时，将尾数再左移 E - 23 位, 此时是由于 num 已经大于 2 ^ 23 ，尾数放不下了所以舍去了 (E - 23) 位，这里将其补回来
        if (E > 23) {
            num = M << (E - 23);
        } 
        // 舍去尾数补 0 的部分
        else {
            /* whether sig is 1 or 0, round to zero */
            num = M >> (23 - E);
        }
    }

    return sig ? -num : num;
}
