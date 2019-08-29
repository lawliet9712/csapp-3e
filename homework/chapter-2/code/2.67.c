/* The following function does not run properly on some machine */
/*
 * int bad_int_size_is_32() {
 *     int set_msb = 1 << 31;
 *     int beyond_msb = 1 << 32;
 *     return set_msb && !beyond_msb;
 * }
 *       */

int int_size_is_32() {
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int int_size_is_16() {
    int set_msb = 1 << 15;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}
