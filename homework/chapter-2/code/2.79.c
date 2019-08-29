/*
 * @note 计算 3 * x / 4
 */

int divide_power2(int x, int k)
{
    return x >= 0 ? x : (x + (1 << k) -1) >> k; 
}

int mul3div4(int x)
{
    x = (x << 1) + x;
    return divide_power2(x, 2);
}
