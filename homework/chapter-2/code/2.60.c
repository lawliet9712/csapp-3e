/*
 * @note 将 x 的第 i 个字节替换为 b
 * @eg replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
 * @eg replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB
 */

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
    // normal check
    unsigned x_size = sizeof(x);
    if( i >=  x_size || i < 0)
        return 0;

    int move_bits = i * 8;
    unsigned res = ((unsigned)b) << move_bits;
    unsigned tmp = x & ~(0xff << move_bits);
    
    return res | tmp;
}
