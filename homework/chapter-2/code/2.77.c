/*
 * @note return x * k, 只使用 + - <<
 */

int x_mul_17(int x)
{
    return (x << 4) + x;
}

int x_mul_neg7(int x)
{
    return x - (x << 3);
}

int x_mul_60(int x)
{
    return (x << 6) - (x << 2);
}

int x_mul_neg112(int x)
{
    return  (x << 4) - (x << 7);
}
