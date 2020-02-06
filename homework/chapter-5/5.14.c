void inner6x1(vec_ptr u, vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(u);
    long limit = length - 5;
    data_t *udata = get_ver_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t)0;

    for (i = 0; i < limit; i += 6) {
        sum = sum + udata[i] * vdata[i] + 
            udata[i + 1] * vdata[i + 1] + 
            udata[i + 2] * vdata[i + 2] + 
            udata[i + 3] * vdata[i + 3] + 
            udata[i + 4] * vdata[i + 4] + 
            udata[i + 5] * vdata[i + 5];
    }

    for (; i < length; i++) {
        sum = sum + udata[i] * vdata[i];
    }

    *dest = sum;
}

A.
在 1x1 的版本中，关键路径只有一个加法, n 不变，6x1 的版本中，关键路径有 6 个加法，但是 n = n / 6, 故该做法仍会有 n 个加法的操作，但是迭代次数减半了，故 CPE 还是有所下降, 这也是因为整数运算的周期较短。
B.
与 A 类似。每次迭代中仍有 n 个浮点加/乘法
