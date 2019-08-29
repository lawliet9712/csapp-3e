/*
 * @note 两数相加
 *       正溢出时返回 TMAX， 负溢出时返回 TMIN
 */

int saturating_add(int x, int y)
{
    int sum = x + y;
    int flag = !((x ^ y) >> 31);

    // 如果符号位相同
    if(flag && (x ^ sum) >> 31)
    {
        if(!(x>>31))
            return 0x7fffffff;
        else
            return 0x80000000;
    }

    return sum;
}
