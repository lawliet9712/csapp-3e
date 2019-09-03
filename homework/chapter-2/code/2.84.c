/*
 * @note 返回 x <= y 的结果
 *       +/- 0 认为是相等的，不存在NaN
 */

unsigned f2u(int x)
{
    union {
        int a;
        float b;
    } tmp;

    tmp.a = x;
    return tmp.b;
}

int float_le(float x, float y)
{
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return sx != sy ? sx > sy : (sx == 0 ? ux <= uy : ux >= uy);
}
