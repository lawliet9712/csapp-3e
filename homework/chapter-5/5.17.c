void * effective_memset(void * s, int c, size_t n)
{
    unsigned long ulong_fill_var = 0;
    int ulong_size = sizeof(unsigned long);
    int shift_bit = ulong_size / 8;
    c &= 0xff;
    for (int i = 0; i < ulong_size; i++)
    {
        ulong_fill_var += c;
        c << shift_bit;
    }

    unsigned char uchar_fill_var = (unsigned char) c;
    int tmp_cnt = n;
    unsigned char * uchar_s = (unsigned char *)s;
    while (tmp_cnt % ulong_size != 0 && tmp_cnt > 0)
    {
        (*uchar_s)++ = uchar_fill_var; 
        tmp_cnt--;
    }
    
    tmp_cnt = n - tmp_cnt;
    int rest_not_algin_cnt = tmp_cnt % ulong_size;
    int loop_times = tmp_cnt / ulong_size; 
    unsigned long * ulong_s = (unsigned long *)uchar_s;
    for (int i = 0; i < loop_times; i++)
    {
        (*ulong_s)++ = ulong_fill_var;
    }
    
    // fill rest space
    uchar_s = (unsigned long *) ulong_s;
    for (int i = 0; i < rest_not_algin_cnt; i++)
    {
        (*uchar_s)++ = uchar_fill_var;
    }

    return NULL;
}
