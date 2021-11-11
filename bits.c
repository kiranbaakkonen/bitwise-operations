/* 
 * CS:APP Data Lab 
 * 
 * Kiran Baakkonen - kbaakkonen
 * 
 * bits.c - Source file with your solutions to the project.
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

You will provide your solution to the project by
editing the collection of functions in this source file.

CODING RULES:
 
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


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function.

/*
 * STEP 2: Modify the following functions according to the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest checker to verify that your solutions produce
 *      the correct answers.
 */


#endif

/************************************************ 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
	
	//first check if number is negative of not
	//if negative, use conditions to return ~x + 1
	//if not negative, return x
	int sign;
	sign = x >> 31;
	
	return ((~sign)&x)|(sign&(~x + 1));
}

/************************************************ 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
	//if x and y have different signs then addition cannot overflow
	//if x and y have the same signs then overflow is possible
	//if the sum of x and y has a different sign then overflow occurred
	//first find all of relevant signs
	//then compare them so that if xsign != ysign it will alwasy return 1
	//but only if xsign == ysign != sumsign return 0;
	int xsign,ysign,sumsign;
	xsign = x >> 31;
	ysign = y >> 31;
	sumsign = (x + y) >> 31;

	return !!((xsign^ysign)|(!(xsign^sumsign)));
}

/************************************************ 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
	//creates int t which has all even bits 1 and all odd bits 0
	// x&t will set x = 0x55555555 if all of the even bits in x are 1
	// then checks if x is 0x55555555 and returns the result
	int t;
	t = ((((((0x55 << 8) + 0x55) << 8) + 0x55) << 8) + 0x55);

	return !((x&t)^t);
}

/************************************************
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	
	// x|-x returns a negative number for every value except zero
	// Every negative number can be turned into -1 by right shifting by 31 bits
	// Adding one to -1 will give 0, but if x|-x was not negative, in the case of 0, it gives 1

	return ((x|(~x + 1)) >> 31) + 1;
}

/************************************************
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */

int bitCount(int x) {

	//First make 4 variables that will each hold 1 mask of x
	//Then make template of 0x11111111 that can be used to get the first bit of every nibble
	//then mask x over template while also shifting x to the right 1 bit per variable so that every 4 bits are masked to different variables
	//Adding x1,x2,x3, and x4 is synonymous with adding each of the ones in the nibbles in the masks
	//Finally, separate the nibbles and add to get the total number of ones in x.

	int temp, x1, x2,x3, x4, tot, nib1, nib2, nib3, nib4, nib5, nib6, nib7, nib8;
	temp = ((((((0x11 << 8) + 0x11) << 8) + 0x11) << 8) + 0x11);

	x1 = x&temp;
	x2 = (x >> 1)&temp;
	x3 = (x >> 2)&temp;
	x4 = (x >> 3)&temp;

	tot = x1 + x2 + x3 + x4;
	
	nib1 = 0xf&tot;
	nib2 = 0xf&(tot >> 4);
	nib3 = 0xf&(tot >> 8);
	nib4 = 0xf&(tot >> 12);
	nib5 = 0xf&(tot >> 16);
	nib6 = 0xf&(tot >> 20);
	nib7 = 0xf&(tot >> 24);
	nib8 = 0xf&(tot >> 28);

	return nib1 + nib2 + nib3 + nib4 + nib5 + nib6 + nib7 + nib8;
}

/************************************************
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
	//returns the bitwise and result of comparing ~x and ~y
	return ((~x)&(~y));
}

/************************************************
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {

	// First move bits beign swapped to least significant
	// fills in rest of integer with 0s , then moves bits to swapped positions
	// empties positions to be swapped in x
	// places bits into correct positions using |	
	int tm, tn;
	tm = ((x >> (m << 3)) & 0xff) << (n << 3);
	tn = ((x >> (n << 3)) & 0xff) << (m << 3);
	x = x & (~(0xff << (m << 3)));
	x = x & (~(0xff << (n << 3)));
	x = x | tm;
	x = x | tn;
	return x;
	
}

/************************************************ 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	//In order to form a conditional, sets x to either 1 or 0 and then subtracts 1
	//this forms a constant of either 0x00000000 or 0xffffffff
	//using the constant formed allows us to essentially delete one outcome 
	//using ~x and x depending on the condition
	//by using | to compare a deleted result with a non deleted result
	//it forms the conditional
	x = !x + (~1 + 1);
	return (x&y)|((~x)&z); //if true, compare 1111 to y
	
}

/************************************************
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
	
	//first multiplies by three to make sure overflow behavior is duplicated
	//then checks if the result if negative
	//if the result if negative, adds 3 to ensure that after right shifiting the result will round up
	// right shift by 2 to get result
	
	int sign, result;

	result = x + x + x;
	sign = result >> 31;
	result = ((~sign)&(result >> 2))|(sign&((result + 3) >> 2));
	return result;	
	
}

/************************************************ 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {

	//value for shifting test = max shift - actual shift
	//left shift truncates value to test if it can fit in n bits and retain its value
	//after being right shifted back
	//if the value after the shifts is the same as the original value then it will fit in n bits
	int diff;
	diff = 32 + ~n +1;
	
	return !(((x << diff) >> diff)^x);
}

/************************************************
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	//shifts the bytes to the right so that the required byte is the least significant
	//then masks the number so that the last byte is the only one showing
	x = (x >> (n << 3));
	return x & 0xff;
}

/************************************************ 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {

	//mulitple shifts of x to the right fill all of the less significant bits of x with ones
	//so that the only 0s in x are the one past the most significant 1
	//if x is positive, then right shifting by 1 will offset the values so that the msb of x is just one above the msb of y
	//Xor of x and y will then create the mask for the greatest positive bit
	//if x is negative, then return 0x800000
	
	int y, mask, neg;
	x = x|(x >> 1);
	x = x|(x >> 2);
	x = x|(x >> 4);
	x = x|(x >> 8);
	x = x|(x >> 16);
	
	y = x >> 1;
	mask = x^y;
	neg = x >> 31; //give 1111 if neg, 0000 if pos
	return (neg&(1 << 31))|((~neg)&mask);
}

/************************************************
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
	//the only situation in which 0 is returned is if x = 1 and y = 0
	//so use (!x)|y so if x is 1 and y is 0 then it will return 0|0
	//in any other case y = 1 or x = 0, so it will return 1
	return ((!x)|y);
}

/************************************************ 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
	
	//Functiosn checks 2 conditions
	//1) First is checks that the second nibble is 3 and that no higher nibbles are filled
	//2) Second is that the first nibble is either between 0-7 or is 8 or 9
	//Then returns the comparison of those tests
	int t1, t2, t3, nib1;
	nib1 = 0xf&x;
	t1 = !((x >> 4)^0x3); // checks if the second nibble is 3 and all higher nibbles 0, -> 1 if true
	t2 = !((nib1) >> 3); //gets first nibble and checks if is is between 0-7
	t3 = !(nib1^0x8)|!(nib1^0x9); //checks is first nibble is either 8 or 9
	
	return t1&(t2|t3);

}
	
/************************************************ 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
	// x^y will return 0 if all the bits are the same
	// so !(x^y) will return 1 if the bits are the same
	return !(x^y);

}

/************************************************
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) 
{
	//First checks signs of vars
	//var is neg -> varsign = -1
	//var is pos -> varsign = 0
	//then forms conditional based off of varsigns
	//if varsigns the same, performs regular subtraction
	//if varsigns are different diff = the sign of x
	//then checks if diff is negative
	//negative diff = less than
	int xsign, ysign, cond, diff;
	
	xsign = x >> 31;
	ysign = y >> 31;

	cond = xsign^ysign; //if same sign, returns 0000, if not returns 1111

	diff = (~cond&(x + (~y +1)))|(cond&x);
	diff = diff >> 31;
	return !!diff;
}

/************************************************
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
	//if value if negative then msbit will be 1
	// arithemetic right shift will either fill with 0s or 1s based on value
	//if value was negative, then x will be -1 and !x will be 0
	//if value was positive, then x will be 0 and 1x will be 1
	x = x >> 31;
	return !x;
}

/************************************************
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {

	//if a number is a power of two, then it can only have 1 bit be 1
	//if 1 is subtracted from that number, then all of the bits below it will be 1
	//First tests for negatives and 0 as those are exceptions.
	//then compare x & x - 1, as if x is a power of two the x & -x will be 0
	int y, isneg, is0;
	isneg = !(x >> 31); //if neg gives 0, if not 1
	is0 = !!x; //if 0 -> 0, if not 1
	y = x + ~0; //if a power of two will be all 1s in a row
	return (!(y&x))&is0&isneg;
}

/************************************************
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
	//Since ~tmin == tmax and tmax + 1 = tmin the expression tmin = ~tmin + 1 can be used
	//to check if x is tmin or not. Since the expression also works for 0, it also needs 
	//to make sure that x is not 0.
	return (!(x^(~x + 1))) & !!x;
}

/************************************************
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
	//-1 is represented as 0xffffffff which is the same as ~0x0;
	return ~0; 
}

/************************************************
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
	//first saves a copy of x in t
	//then shifts x to the left by n
	//then gets the bits that must be replaced in x by right shifting t
	//by 32 - n
	//next creates a mask for t by multiply 1 by 2^n and then subtracting 1
	//final step fits t into missing parts of x
	int t;
	t = x;
	x = x << n;
	t = t >> (32 + (~n + 1));
	t = t & ((1 << n) + (~1 + 1));
	
	return x|t;
}

/************************************************
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {

	//first obtains sign of x and then the sign of 2x
	//if the sign of x and 2x are the same, then no overflow occurred, so return 2x
	//if the signs are not the same then base off of the sign of 2x
	//if 2x is negative, return tmax
	//if 2x is positive, return tmin
	int sign, two, twosign, tmin;
	sign = x >> 31; //if x is negative, sign is -1, is not sign is 0
	two = x + x;
	twosign = two >> 31;

	tmin = 1 << 31;

	return (~(sign^twosign)&two)|((sign^twosign)&((twosign&(~tmin))|((~twosign)&tmin)));


}







