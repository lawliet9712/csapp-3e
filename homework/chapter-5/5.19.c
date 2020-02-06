void psum_4_1a(float a[], float p[], long n)
{
    long i = 4;
    float tmp = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
    // warn
    for (i = 0; i < n - 3; i += 4) {
        tmp = tmp3 + a[i];
        tmp1 = tmp + a[i + 1];
        tmp2 = tmp1 + a[i + 2];
        tmp3 = tmp2 + a[i + 3];

        p[i] = tmp;
        p[i + 1] = tmp1;
        p[i + 2] = tmp2;
        p[i + 3] = tmp3;
    }

    for (; i < n; i++) {
        tmp3 += a[i];
        p[i] = tmp3;
    }
}

