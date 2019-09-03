/*
 * @note 返回一个从最高位开始有连续 w-k 个 1 加上连续 k 个 0
 */

int A(int k)
{
    return (-1 << k);
}

/*
 * @note 返回一个从最高位开始有连续 w-k-j 个 0 加上连续 k 个 1 再加上 j 个 0
 */

int B(int j, int k)
{
    return (~(-1 << k)) << j;
}
