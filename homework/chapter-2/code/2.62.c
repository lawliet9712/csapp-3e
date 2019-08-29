/*
 * @note 对 int 使用算术右移的机器上返回 1
 *       应当适用于任何字长的机器
 */

int int_shifts_are_arithmetic()
{
    return !((-1 >> 1) ^ -1);
}
