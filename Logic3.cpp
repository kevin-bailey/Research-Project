#include "stdafx.h"
#include "Logic3.h"

#define FALSE 0
#define UNCERTAIN 1
#define TRUE 2

Logic3::Logic3()
{
}

int Logic3::KAND(int a, int b) {
	// Kleene AND
	// Returns FALSE if any trit is FALSE
	// Returns TRUE if both trits are TRUE
	/* 0 0 0
	0 1 1
	0 1 2
	*/
	if (a == FALSE || b == FALSE) return FALSE;
	if (a == UNCERTAIN || b == UNCERTAIN) return UNCERTAIN;
	return TRUE;
}

int Logic3::KOR(int a, int b) {
	// Kleene OR
	// Returns TRUE if any trit is TRIE
	// Returns FALSE if both trits are FALSE
	/* 0 1 2
	1 1 2
	2 2 2
	*/
	if (a == TRUE || b == TRUE) return TRUE;
	if (a == UNCERTAIN || b == UNCERTAIN) return UNCERTAIN;
	return FALSE;
}

int Logic3::TAND(int a, int b) {
	// Ternary NAND
	// Returns UNCERTAIN if any trit is FALSE or UNCERTAIN
	/* 1 1 1
	1 0 0
	1 0 0
	*/
	if (a == FALSE || b == FALSE) return UNCERTAIN;
	return FALSE;
}

int Logic3::TOR(int a, int b) {
	// Ternary NOR
	// Returns UNCERTAIN if any trit is TRUE or UNCERTAIN
	/* 0 0 1
	0 0 1
	1 1 1
	*/
	if (a == TRUE || b == TRUE) return UNCERTAIN;
	return FALSE;
}

int Logic3::BAND(int a, int b) {
	// Binary NAND
	// Returns TRUE if any trit is FALSE
	// Otherwise return FALSE
	/* 2 2 2
	2 0 0
	2 0 0
	*/
	if (a == FALSE || b == FALSE) return TRUE;
	return FALSE;
}

int Logic3::BOR(int a, int b) {
	// Binary NOR
	// Returns TRUE if any trit is TRUE
	// Otherwise return FALSE
	/* 0 0 2
	0 0 2
	2 2 2
	*/
	if (a == TRUE || b == TRUE) return TRUE;
	return FALSE;
}

int Logic3::NOT(int a) {
	if (a == TRUE) return FALSE;
	if (a == FALSE) return TRUE;
	return UNCERTAIN;
}

int Logic3::REM(int a, int b) {
	// This "gate" calculates the remainder of 2 trits
	/* 0 0 0
	0 0 1
	0 1 1
	*/
	return (KAND(TOR(a, b), KAND(a, b)));
}

int Logic3::SUM(int a, int b) {
	// This "gate" calculates the sum of two trits
	/* 0 1 2
	1 2 0
	2 0 1
	*/
	return (KAND(CTRL(a, b), KOR(KAND(NOT(REM(a, b)), KOR(a, b)), NOT(KOR(BOR(a, b), BAND(a, b))))));
}

int Logic3::CTRL(int a, int b) {
	// This "gate" is used nothing more as a catalyst for our adder
	// In truth, we don't even need this method, but it will look neater in the code.
	/* 2 2 2
	2 2 0
	2 0 2
	*/
	return (BOR(UNCERTAIN, KOR(KAND(KAND(a, b), KOR(BOR(a, b), BAND(a, b))), NOT(KAND(KAND(a, b), KOR(BOR(a, b), BAND(a, b)))))));
}

void Logic3::ADD(int a, int b, int cin, int& cout, int& sum) {
	/* cout = SUM(a, b);
	sum = SUM(cout, cin);
	cout = REM(a, b); */

	sum = SUM(cin, SUM(a, b));
	cout = KOR(REM(a, b), REM(cin, SUM(a, b)));
}

int Logic3::ternaryConversion(int decimalNum) {
	if (decimalNum <= 2) return decimalNum;
	int carry = decimalNum % 3;
	ternaryConversion(decimalNum >> 2);
	return carry;
}

Logic3::~Logic3()
{
}
