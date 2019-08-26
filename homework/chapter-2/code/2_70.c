/*
 * @note 当 x 可以被 n 位表示时，返回 1
 */
int fits_bits(int x, int n)
{
    return !(x & (-1 << n));
}
