/*
 * @note 当 x 的任意奇数位为 1 时返回 1
 *       假设 int 为 32 位
 */
int any_odd_one(unsigned x)
{
    return !!(x & 0xAAAAAAAA);
}
