/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    return ~(x&y) & (~(~x & ~y)); 
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    return !(~(x ^ (x + 1))) & !!(~x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    int a = 0xAA | 0xAA << 8;
    a = a | 0xAA << 16;
    a = a | 0xAA << 24;
    return !((a&x)^a);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    int max = (0x39 + (~x + 1)) >> 31;
    int min = (x + (~0x30 + 1)) >> 31;
    return ((max | min) & 1) ^ 1;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    x = (!!x) << 31 >> 31;
    return (x & y) | (~x & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */

// 判断 y-x 即可
// 此时只需要考虑符号不同的情况，符号相同的情况不会溢出
// 符号不同时可能会负溢出，需要特殊处理
// 符号不同负溢出的情况只存在于 y 为整数， x 为负数
// 此时只需要返回 y 的符号位即可

int isLessOrEqual(int x, int y) {
    // 符号是否一致
    int a = !(y>>31 ^ x>>31);

    // 符号一致时，a = 1，置反 a 使判断符号的结果为 0 
    // 当符号不一致时，a = 0 ， 使判断 y-x 的结果为 0 
    // 两种情况下 a 分别为另一边的掩码, 将另一边的结果置为0，避免影响结果
    
    int b = a & !((y + ~x + 1) >> 31);
    return ((!(y>>31)) & ~a) | b;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */

// 只有 0 和 INT_MIN 取其负数, 符号位不会改变
// 正常情况下如果符号位不同 或者 x 为 INT_MIN 则返回 0 
// 其他情况返回 1
int logicalNeg(int x) {
    int y = ~x + 1;

    // sign 为 1 时表示符号位不同
    // 此时函数应该返回 0 ，但如果 xIsNeg 为 1, 则应该返回 1 。
    int sign = (y >> 31 ^ (x >> 31)) & 1;
    int xIsNeg = ((x >> 31) & 1);

    int a = (sign | xIsNeg);

    // 此时 a 要么为 1 要么为 0
    // 需要将结果置反才可得到正确答案
    return a ^ 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */

// 返回需要多少位才可以表示 x 的二进制补码
// x的最高位前面必定全为 0 或者全为 1
// x ^ (x << 1) 可以得到最高位为 1 的位置即是表示 x 所需的位数
// 采用类似二分法的思想
// 每次右移 x 位，如果右移后 !! 的值为 1 ，说明其最高位定然在最高有效 x 位那边
// 此时起码需要低x位才可以表示 x ，因为每次都是对半进行查找
// 结果需要加 1， 因为最少也需要 1 位才可表示 x
// 此外 16 + 8 + 4 + 2 + 1 为 31，最高只能表示 31 位，而如 TMIN 实际上需要 32 位
int howManyBits(int x) {
    int tmp = x ^ (x << 1);
    int bit_16 = !!(tmp >> 16) << 4;
    tmp = tmp >> bit_16;
    int bit_8 = !!(tmp >> 8) << 3;
    tmp = tmp >> bit_8;
    int bit_4 = !!(tmp >> 4) << 2;
    tmp = tmp >> bit_4;
    int bit_2 = !!(tmp >> 2) << 1;
    tmp = tmp >> bit_2;
    int bit_1 = !!(tmp >> 1);

    return bit_16 + bit_8 + bit_4 + bit_2 + bit_1 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

// 将 uf 视为浮点数, 返回其 * 2 之后的值
// 浮点数的计算公式为 V = (-1)^S * M * 2^E
// 其中 S为符号位，M 为尾数，E为阶码值
// 浮点数扩大 2 倍即 V * 2
// 浮点数有规格化值和非规格化值以及 NaN
// NaN 时直接返回，现在考虑规格化和非规格化的 E 值
// 规格化 E = e - 127  , 非规格化 E = 1 - 127
// 非规格化情况下，由于阶码位全为 0，所以将 uf << 1 即可
// 此时若左移到阶码位最低位，也不影响阶码值，且此时 M = 1 + f
// 需要注意保留符号位
// 规格化情况下，使 e + 1，即阶码位加 1 
unsigned floatScale2(unsigned uf) {
    unsigned S = (uf >> 31) & 1;
    unsigned e = (uf >> 23) & 0xFF;

    // 非规格化
    if(e == 0)
    {
        return (uf << 1) | (S << 31);
    }

    // NaN
    if(e == 0XFF)
    {
        return uf;
    }
    // 规格化值
    else
    {
        return uf + (1 << 23);
    }
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
