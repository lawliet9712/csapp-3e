/*
 * @note 当 x 包含奇数个 1 时返回 1
 *       假设 int 为 32 位
 */
int odd_ones(unsigned x)
{
    x = x >> 16 ^ x;
    x = x >> 8 ^ x;
    x = x >> 4 ^ x;
    x = x >> 2 ^ x;
    x = x >> 1 ^ x;

    return x & 1;
}
