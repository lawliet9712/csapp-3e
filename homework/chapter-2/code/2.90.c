float fpwr2(int x) {
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    if (x < 2-pow(2,7)-23) {
        /* too small. return 0.0 */
        exp = 0;
        frac = 0;

    } else if (x < 2-pow(2,7)) {
        /* Denormalized result */
        exp = 0;
        frac = 1 << (unsigned)(x - (2-pow(2,7)-23));

    } else if (x < pow(2,7)-1+1) {
        /* Normalized result */
        exp = pow(2,7)-1+x;
        frac = 0;

    } else {
        /* Too big, return +oo */
        exp = 0xFF;
        frac = 0;

    }

    /* pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Result as float */
    return u2f(u);
}
