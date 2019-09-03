typedef unsigned float_bits;

float_bits float_half(float_bits f) {
    unsigned sig = f >> 31;
    unsigned rest = f & 0x7FFFFFFF;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    int is_NAN_or_oo = (exp == 0xFF);
    if (is_NAN_or_oo) {
        return f;
    }

    /*
     *  这里需要注意取整的情况, 假设这个被右移出去的位为a，那么a就有可能是1或者0，如果是0，那么我们
     *  就不需要取整，如果是1，我们可以这么想：1111.a 这个a如果是1，折算成小数就是0.5 因此是需要
     *  取整的，它前边的那一位如果是0，表示已经是偶数了，就舍弃a 如果是1，要向上取整，在未右移之前+1就可以了
     */

    int addition = (frac & 0x3) == 0x3;

    if (exp == 0) {
        /* Denormalized */
        frac >>= 1;
        frac += addition;
    } else if (exp == 1) {
        /* Normalized to denormalized */
        // 这里需要特殊处理
        // exp == 1 的时候，阶码的值仍然为 1 - 127
        // 而尾数的值变成了 (1 + frac)
        // 除以2即 (1 + frac) / 2
        // 所以只需要将尾数部分右移，再将尾数部分最高位置一即可
        // 最高位置 1 即表示尾数部分加上 1/2

        rest >>= 1;
        rest += addition;

        // 等价 exp = 0
        exp = rest >> 23 & 0xFF;
        frac = rest & 0x7FFFFF;
    } else {
        /* Normalized */
        exp -= 1;
    }

    return sig << 31 | exp << 23 | frac;
}
