/*
 * @note x / (2^k) , 采用正确的舍入方式
 *       只需考虑负数情况下，有小数需要向上舍入
 */
int divide_power2(int x, int k)
{
    return x >= 0 ? x : (x + (1 << k) -1) >> k; 
}
