/*
 * @note int x = random(); int y = random();
 *       unsigned ux = (unsigned)x;
 *       unsigned uy = (unsigned)y;
 *       判断下列等式是否成立
 *       (x < y) == (-x > -y)                           ==> false (x == INT_MIN)
 *       ((x + y) << 4 )+ y - x == 17 * y + 15 * x      ==> true
 *       ~x + ~y + 1 = ~(x + y)                         ==> true
 *       ux - uy == -(unsigned)(y - x)                  ==> true
 *       ((x >> 2) << 2) <= x                           ==> true
 */
