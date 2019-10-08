long cread(long *xp) {
    return (xp ? *xp : 0);
}

long cread_alt(long *xp) {
    return (!xp ? 0 : *xp);
}

// 上题考察的重点应当是如何使用条件传送指令时避免解引用空指针, 但是实际上测试的时候不管怎么书写都无法使用条件传送指令,可能与优化级别有关
