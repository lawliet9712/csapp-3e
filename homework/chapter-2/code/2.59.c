/*
 * @note 返回一个由 a 的最低有效字节和 b 的余下字节组合成的字
 * @eg a = 0x89ABCDEF , b = 0x76543210, return 0x765432EF
 */
unsigned get_expr(unsigned a, unsigned b)
{
    unsigned res = a & 0xff;
    unsigned tmp = b >> 8 << 8;
    return res | tmp;
}
