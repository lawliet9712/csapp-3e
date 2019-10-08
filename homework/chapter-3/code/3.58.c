long decode2(long x, long y, long z)
{
    return ((y-z) * x) ^ ((y-z) << 63 >> 63);
}
