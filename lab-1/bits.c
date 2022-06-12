/* 
 * <Name: Rena Zhao (ryz215)>
 * <GitHub name: ryzhao123>
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
  int result = ~(~(x & ~y) & ~(~x & y));
  return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int result = 1 << 31;
  return result;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  int result = !(~(x ^ (x + 1)) + !(x + 1));
  return result;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int compare = 170 + (170 << 8) + (170 << 16) + (170 << 24); // 0xAAAAAAAA
  int result = !((x & compare) ^ compare);
  return result;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  int result = ~x + 1;
  return result;
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
  int upper = (0x39 + (~x + 1)) >> 31; // 0x39 + (~x + 1) >= 0
  int lower = (x + (~0x30 + 1)) >> 31; // x + (~0x30 + 1) >= 0
  return !upper & !lower;  
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int condition = ~(!x) + 1;
  return (~condition & y) | (condition & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int signbit_x = (x >> 31) & 1; // sign bit of x
  int signbit_y = (y >> 31) & 1; // sign bit of y
  int signbit_difference = ((y + (~x + 1)) >> 31) & 1; // sign bit of y-x
  return ((signbit_x ^ signbit_y) & signbit_x) | (!signbit_difference & !(signbit_x ^ signbit_y));
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
int logicalNeg(int x) {
  int result = ((x | (~x + 1)) >> 31) + 1;
  return result;
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
int howManyBits(int x) {
  int bits16, bits8, bits4, bits2, bit1, bit0;
  int sign = x >> 31;  // sign bit
  x = (sign & ~x) | (~sign & x);  // flips negative numbers
  bits16 = !!(x >> 16) << 4;  // first 16 bits
  x = x >> bits16; // shift if bits16 = 16
  bits8 = !!(x >> 8) << 3;  // next 8 bits
  x = x >> bits8;
  bits4 = !!(x >> 4) << 2; // etc.
  x = x >> bits4;
  bits2 = !!(x >> 2) << 1;
  x = x >> bits2;
  bit1 = !!(x >> 1);
  x = x >> bit1;
  bit0 = x;
  return bits16 + bits8 + bits4 + bits2 + bit1 + bit0 + 1;  // add 1 for sign bit
}
//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  int sign = uf & (1 << 31);  // sign bit
  int exponent = (uf >> 23) & 255;  // exponent bits
  
  if (exponent == 255) {  // return input if infinity or NaN
    return uf;
  }

  if (exponent == 0) { // denormalized number
    return (uf << 1) | sign; 
  } 

  exponent = exponent + 1; // adding 1 is equivalent to x2
  if (exponent == 255) {  // check overflow
    return 0x7F800000 | sign; 
  }
  else { 
    int fraction = uf & 0x7FFFFF;  // fraction bits
    return (fraction | exponent << 23) | sign;  // add all components together
  }
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  int sign, exponent, fraction;
  sign = x & (1 << 31);
  exponent = 158;
  if (!x) {  // x = 0
    return 0;
  }
  if (x == (1 << 31)) { // x = minimum TC integer
    return 0xCF000000;
  }
  if (sign) { // TC if negative
    x = ~x + 1;
  }
  while (!(x & (1 << 31))) { // find the first instance of 1
    x = x << 1;
    exponent--;
  }
  fraction = (x & ~(1 << 31)) >> 8; // build fraction
  if ((x & 128) && ((x & 127) > 0 || fraction & 1)) { // rounding 
    fraction++;
  }
  return sign + (exponent << 23) + fraction;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
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
int float_f2i(unsigned uf) {
  int exponent = (uf >> 23) & 255; // exponent bits
  int fraction = uf & 0x7FFFFF; // fraction bits
  int sign = uf & (1 << 31); // sign bit
  int e = exponent - 127; // weights value by power of 2

  if (exponent == 0x7F800000) { // if exponent is all 1s
    return 0x80000000u;
  }
  if (e > 30) { // power of 2 too large
    return 0x80000000u;
  }
  if(!exponent) { // exponent is 0
    return 0;
  }
  if (e < 0) { // negative power of 2 
    return 0;
  }
  fraction = fraction | 0x800000; // append hidden 1 to fraction
  if (e >= 23) {
    fraction = fraction << (e - 23); // left shift to make bigger
  }
  else {
    fraction = fraction >> (23 - e); // right shift to make smaller
  }
  if (sign) {
    return ~fraction + 1; // TC if negative
  }
  return fraction;
}
