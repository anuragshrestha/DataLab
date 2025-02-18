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
  1. Use any c  ontrol constructs such as if, do, while, for, switch, etc.
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
/* Copyright (C) 1991-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */

/*
 * This function returns the count of the number of 1's (set bits) in a 32-bit integer.
 * The function bitCount uses a series of bitwise masks and shifts to efficiently sum the bits.
 * It progressively reduces the number of bits to count by grouping them in larger
 * blocks with each step.
 *
 * Approach:
 *     1. Initialize various masks to isolate and sum groups of bits.
 *     2. Use bitwise AND (`&`) to isolate the bits in the groups
 *      defined by each mask.
 *     3. Sum the bits in the groups and progressively shift and mask
 *      to handle larger groups.
 *     4. Finally, sum the counts of all the 1's in the 32-bit word.
 *
 *   Steps I followed:
 *     - mask1 isolates pairs of bits (010101...).
 *     - mask2 isolates groups of 4 bits (00110011...).
 *     - mask4 isolates groups of 8 bits (00001111...).
 *     - mask8 isolates groups of 16 bits.
 *     - mask16 isolates groups of 32 bits.
 *     Each step reduces the number of bits until the total
 *       count of 1's is computed.
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
       
         int mask1 = 0x55 | (0x55 << 8);
         mask1 = mask1 | (mask1 << 16);

         int mask2 = 0x33 | (0x33 << 8);
         mask2 = mask2 | (mask2 << 16);

         int mask4 = 0x0F | (0x0F << 8);
         mask4 = mask4 | (mask4 << 16);

         int mask8 = 0xFF | (0xFF << 16);
         int mask16 = 0xFF | (0xFF << 8);


         x = (x & mask1) + ((x >> 1) & mask1);
         x = (x & mask2) + ((x >> 2) & mask2);
         x = (x & mask4) + ((x >> 4) & mask4);
         x = (x & mask8) + ((x >> 8) & mask8);
         x = (x & mask16) + ((x >> 16) & mask16);

         return x;
     }

/*
* Approach:
* This function performs a bitwise NOR operation on two integers, x and y,
* using only the bitwise NOT (~) and AND (&) operators. NOR is the complement
* of the OR operation, meaning that for any bit where either x or y has a 1,
* the result will be 0. For any bit where both x and y are 0, the result will be 1.

* Steps I Followed:
* The problem requires the implementation of a bitwise NOR operation, which
* is the complement of the OR (|) operation. Normally, we would compute x | y
* and then negate the result, but we’re restricted to using only the ~ and
* & operators.
* Apply De Morgan's Law: Using De Morgan's law:
* ~(x | y) can be rewritten as ~x & ~y.
* This transformation eliminates the need for the OR operator, allowing us to express
* the NOR operation with only NOT and AND.
* I applied the bitwise NOT operation to both x and y individually, which inverts
*  the bits in both integers.
* After inverting x and y, I applied the bitwise AND operation. This ensures that only
* the bits where both ~x and ~y are 1 will remain set to 1 in the result. This effectively
* implements the NOR operation.
* The result of the AND operation between ~x and ~y gives us the desired result
* for ~(x | y) bitNor - ~(x|y) using only ~ and &
*   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
*   Legal ops: ~ &
*   Max ops: 8
*   Rating: 1
*/
int bitNor(int x, int y) {
  return ~x & ~y;
}
/*
 *The `byteSwap` function swaps two specified bytes (the `nth` and `mth` bytes)
 * in a 32-bit integer. To do this, I first calculated the bit
 * positions of these bytes by shifting `n` and `m` by 8.
 * I then extracted the `nth` and `mth` bytes by shifting the integer
  to isolate  the target bytes and masking the result with `0xFF`.
 * After extracting these bytes, it clears the original bytes in the integer using
  a mask and the bitwise AND operation.
 * Finally, we inserts the bytes in their swapped positions using the bitwise
 * OR operation. This ensures that the two bytes are swapped while leaving the rest of
 * the integer unchanged.


 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {

    int n_shift = n << 3;
    int m_shift = m << 3;

    int n_byte = (x >> n_shift) & 0xFF;
    int m_byte = (x >> m_shift) & 0xFF;

    int mask = (0xFF << n_shift) | (0xFF << m_shift);
      x = x & ~mask;
      x = x | (n_byte << m_shift) | (m_byte << n_shift);

      return x;
}
/*
 * Approach:
 * This function multiplies an integer by 3/4, with the result rounded
 * toward zero. The challenge is to efficiently perform this operation
 * using only bitwise operators and addition, while handling overflow
 * correctly and ensuring rounding behaves as expected for both positive
 * and negative numbers.
 *
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {

      int three = (x << 1) + x;
      int bias = (three >> 31) & 3;

   return (three + bias) >> 2;
}
/*
 * Approach
 * To solve the `float_abs` function, I first created a mask `m = 0x7FFFFFFF`
 * to clear the sign bit of the floating-point number, effectively obtaining
 * the absolute value by applying the mask using the bitwise AND operation (`uf & m`).
 * Then, to handle NaN (Not a Number) cases, I compared the result to the smallest
 * NaN value, `min = 0x7F800001`. If the result was equal to or greater than
 * this value, I returned the original input `uf` (indicating it was a NaN).
 * Otherwise, I returned the masked result `res`, which is the absolute value
 * of the input.
 *
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {

    unsigned m = 0x7FFFFFFF;
    unsigned min = 0x7F800001;
    unsigned res = uf & m;

       if (res >= min)
      {
          return uf;
       }
         else
       {
          return res;
        }
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {

   if (((uf << 1) >> 24) == 0xFF && ((uf << 9) != 0))
      return uf;
   return (1 << 31) ^ uf;
}
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

     int dif = (x >> 4) ^ 0x3;
     int isValid= ((0x0f & x) + 0x6) & 0xf0;

         return !(dif | isValid);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {

   int pos = x >> 31;

   return !(pos | (!x));
}
