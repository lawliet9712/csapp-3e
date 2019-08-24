/*
 * @note x 全为 1 返回 1
 */
int any_bit_eq_one(int x)
{
    return !~x;
}

/*
 * @note x 全为 0 返回 1
 */
int any_bit_eq_zero(int x)
{
    return !x;
}

/*
 * @note x 最低有效字节中的位都为 1 返回 1
 */
int lower_bit_eq_one(int x)
{
    return !(~x & 0xff);
}

/*
 * @note x 最高有效字节中的位都为 0 返回 1
 */
int higher_bit_eq_one(int x)
{
    return !(x >> 24);
}
