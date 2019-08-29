#include <limits.h>
/*
 * @note 如果 x - y 不溢出，则返回 1 
 */
int tsub_ok(int x, int y)
{
    if(y == INT_MIN)
        return 0;

    int sum = x + y;
    int neg_over = x < 0 && y < 0 && sum >= 0;
    int pos_over = x >= 0 && y >= 0 && sum < 0;

    return !neg_over && !pos_over;
}
