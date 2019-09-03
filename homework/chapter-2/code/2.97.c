/*
 *  * float-i2f.c
 *   */
#include <stdio.h>
#include <assert.h>
#include <limits.h>

typedef unsigned float_bits;

int bits_length(int i) {
    if ((i & INT_MIN) != 0) {
        return 32;

    }

    unsigned u = (unsigned)i;
    int length = 0;
    while (u >= (1<<length)) {
        length++;

    }
    return length;

}

/*
 ** 生成掩码
 ** 00000...(32-l) 11111....(l)
 **
 ** e.g.
 ** 3  => 0x00000007
 ** 16 => 0x0000FFFF
 **/
unsigned bits_mask(int l) {
    return (unsigned) -1 >> (32-l);
}

float_bits float_i2f(int i) {
    unsigned sig, exp, frac, rest, exp_sig /* except sig */, round_part;
    unsigned bits, fbits;
    unsigned bias = 0x7F;

    if (i == 0) {
        sig = 0;
        exp = 0;
        frac = 0;
        return sig << 31 | exp << 23 | frac;
    }

    if (i == INT_MIN) {
        sig = 1;
        exp = bias + 31;
        frac = 0;
        return sig << 31 | exp << 23 | frac;
    }

    sig = 0;

    // 由于浮点数负数只是符号位不同
    // 如果 i 是负数，取反, 获取其正数的位表示
    if (i < 0) {
        sig = 1;
        i = -i;

    }

    bits = bits_length(i);
    fbits = bits - 1;
    exp = bias + fbits;

    rest = i & bits_mask(fbits);

    // 当 fbits 小于 23 位时，没有被舍去的位，因此可以正常表示
    if (fbits <= 23) 
    {
        frac = rest << (23 - fbits);
        exp_sig = exp << 23 | frac;
    } 
    // 此时需要考虑舍入的问题
    // 具体参考 csapp 3e p83
    // 向偶数舍入
    else 
    {
        int offset = fbits - 23;
        int round_mid = 1 << (offset - 1);

        round_part = rest & bits_mask(offset);
        frac = rest >> offset;
        exp_sig = exp << 23 | frac;

        /* round to even */
        if (round_part < round_mid) {
            /* nothing */

        } else if (round_part > round_mid) {
            exp_sig += 1;

        } else {
            /* round_part == round_mid */
            if ((frac & 0x1) == 1) {
                /* round to even */
                exp_sig += 1;
            }

        }
    }

    return sig << 31 | exp_sig;
}
