/*
 * @note see 2.71
 */
int xbyte(unsigned word, int bytenum)
{
    int size = sizeof(unsigned);
    int shift_left_val = (size - 1 - bytenum) << 3;
    int shift_right_val = (size - 1) << 3;
    return (int) word << shift_left_val >> shift_right_val;
}
