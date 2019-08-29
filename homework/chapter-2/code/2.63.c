/*
 *  @note see 2.63
 */

// 将前 k 位置 0
unsigned srl(unsigned x, int k)
{
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;

    int move_bits = sizeof(int) * 8 - k;
    int tmp = -1 << move_bits;
    
    return xsra & ~tmp;
}

// 将前 k 位置 1
unsigned sra(unsigned x, int k)
{
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;

    int move_bits = sizeof(int) * 8 - k;
    int tmp = -1 << move_bits;

    return xsrl | tmp;
}
