
int absVal(int x) {
	
	//first check if number is negative of not
	//if negative, use conditions to return ~x + 1
	//if not negative, return x
	int sign;
	sign = x >> 31;
	
	return ((~sign)&x)|(sign&(~x + 1));
}

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


int allEvenBits(int x) {
	//creates int t which has all even bits 1 and all odd bits 0
	// x&t will set x = 0x55555555 if all of the even bits in x are 1
	// then checks if x is 0x55555555 and returns the result
	int t;
	t = ((((((0x55 << 8) + 0x55) << 8) + 0x55) << 8) + 0x55);

	return !((x&t)^t);
}

int bang(int x) {
	
	// x|-x returns a negative number for every value except zero
	// Every negative number can be turned into -1 by right shifting by 31 bits
	// Adding one to -1 will give 0, but if x|-x was not negative, in the case of 0, it gives 1

	return ((x|(~x + 1)) >> 31) + 1;
}

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

int bitNor(int x, int y) {
	//returns the bitwise and result of comparing ~x and ~y
	return ((~x)&(~y));
}

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

int fitsBits(int x, int n) {

	//value for shifting test = max shift - actual shift
	//left shift truncates value to test if it can fit in n bits and retain its value
	//after being right shifted back
	//if the value after the shifts is the same as the original value then it will fit in n bits
	int diff;
	diff = 32 + ~n +1;
	
	return !(((x << diff) >> diff)^x);
}

int getByte(int x, int n) {
	//shifts the bytes to the right so that the required byte is the least significant
	//then masks the number so that the last byte is the only one showing
	x = (x >> (n << 3));
	return x & 0xff;
}

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

int implication(int x, int y) {
	//the only situation in which 0 is returned is if x = 1 and y = 0
	//so use (!x)|y so if x is 1 and y is 0 then it will return 0|0
	//in any other case y = 1 or x = 0, so it will return 1
	return ((!x)|y);
}

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
	
int isEqual(int x, int y) {
	// x^y will return 0 if all the bits are the same
	// so !(x^y) will return 1 if the bits are the same
	return !(x^y);

}

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

int isNonNegative(int x) {
	//if value if negative then msbit will be 1
	// arithemetic right shift will either fill with 0s or 1s based on value
	//if value was negative, then x will be -1 and !x will be 0
	//if value was positive, then x will be 0 and 1x will be 1
	x = x >> 31;
	return !x;
}

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

int isTmin(int x) {
	//Since ~tmin == tmax and tmax + 1 = tmin the expression tmin = ~tmin + 1 can be used
	//to check if x is tmin or not. Since the expression also works for 0, it also needs 
	//to make sure that x is not 0.
	return (!(x^(~x + 1))) & !!x;
}

int minusOne(void) {
	//-1 is represented as 0xffffffff which is the same as ~0x0;
	return ~0; 
}

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







