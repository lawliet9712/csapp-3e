#include <inttypes.h>

/*
 * @note 计算 x * y 的高 w 位
 *       只需注意符号位
 */
int signed_high_prod(int x, int y) {
    int64_t mul = (int64_t) x * y;
    return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int sig_x = x >> 31;
    int sig_y = y >> 31;
    int signed_prod = signed_high_prod(x, y);
    return signed_prod + x * sig_y + y * sig_x;

}

unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
    uint64_t mul = (uint64_t) x * y;
    return mul >> 32;
}
