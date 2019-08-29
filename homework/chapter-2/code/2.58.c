/*
 *  @note 在小端机器上编译运行时返回 1，大端机器上编译运行返回 0
 */
int is_little_endian()
{
    union {
        int a;
        unsigned char b;
    }a;

    a.a = 1;
    unsigned char *pa = &a.b;

    if(*pa == 0x1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}   
