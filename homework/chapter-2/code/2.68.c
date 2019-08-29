/*
 * @note 使[1, n]的位全部为 1
 */

int lower_one_mask(int n)
{
    return ~((-1) << n);
}
