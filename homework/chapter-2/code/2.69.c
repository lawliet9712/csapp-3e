/*
 * @note 将 x << n 位，并且将溢出的 n 位置于 x 的低 n 位 
 * @eg x = 0x12345678, n = 4, result = 0x23456781
 */

unsigned rotate_left(unsigned x, int n)
{
    int w = sizeof(unsigned) << 3;
    return x << n | x >> (w - n);
}
