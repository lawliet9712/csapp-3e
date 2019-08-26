/*
 * @note 生成一个掩码，使 x 只保留最左边的 1
 *       假设 int 为 32 位
 *       不能超过 15 次运算
 * @eg 0xFF00 -> 0X8000 , 0X6600 -> 0X4000
 */
int leftmost_one(unsigned x)
{
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);

    return x & ~(x >> 1);
}
