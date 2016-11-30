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
	/* 
	0 0 0
	0 1 1
	0 1 2
	*/
	if (a == FALSE) return FALSE;
	if (b == FALSE) return FALSE;
	if (a == UNCERTAIN) return UNCERTAIN;
	if (b == UNCERTAIN) return UNCERTAIN;
	return TRUE;
}

int Logic3::KOR(int a, int b) {
	// Kleene OR
	// Returns TRUE if any trit is TRUE
	// Returns FALSE if both trits are FALSE
	/* 
	0 1 2
	1 1 2
	2 2 2
	*/
	if (a == TRUE) return TRUE;
	if (b == TRUE) return TRUE;
	if (a == UNCERTAIN) return UNCERTAIN;
	if (b == UNCERTAIN) return UNCERTAIN;
	return FALSE;
}

int Logic3::TAND(int a, int b) {
	// Ternary NAND
	// Returns UNCERTAIN if any trit is FALSE
	/* 
	1 1 1
	1 0 0
	1 0 0

	Note: this is actually not part of the ternary adder right now,
	but it is still present in the logic system used to construct it.
	if anyone thinks they can improve upon the adder using it, please do!
	*/
	if (a == FALSE) return UNCERTAIN;
	if (b == FALSE) return UNCERTAIN;
	return FALSE;
}

int Logic3::TOR(int a, int b) {
	// Ternary NOR
	// Returns UNCERTAIN if any trit is TRUE
	/* 
	0 0 1
	0 0 1
	1 1 1
	*/

	if (a == TRUE) return UNCERTAIN;
	if (b == TRUE) return UNCERTAIN;
	return FALSE;
}

int Logic3::BAND(int a, int b) {
	// Binary NAND
	// Returns TRUE if any trit is FALSE
	// Otherwise return FALSE
	/* 
	2 2 2
	2 0 0
	2 0 0
	*/
	if (a == FALSE) return TRUE;
	if (b == FALSE) return TRUE;
	return FALSE;
}

int Logic3::BOR(int a, int b) {
	// Binary NOR
	// Returns TRUE if any trit is TRUE
	// Otherwise return FALSE
	/* 
	0 0 2
	0 0 2
	2 2 2
	*/
	if (a == TRUE) return TRUE;
	if (b == TRUE) return TRUE;
	return FALSE;
}

int Logic3::NOT(int a) {
	if (a == TRUE) return FALSE;
	if (a == FALSE) return TRUE;
	return UNCERTAIN;
}

int Logic3::REM(int a, int b) {
	// This "gate" calculates the remainder of 2 trits
	/* 
	0 0 0
	0 0 1
	0 1 1
	*/
	return (KAND(TOR(a, b), KAND(a, b)));
}

int Logic3::SUM(int a, int b) {
	// This "gate" calculates the sum of two trits
	/* 
	0 1 2
	1 2 0
	2 0 1
	*/
	return (KAND(CTRL(a, b), KOR(KAND(NOT(REM(a, b)), KOR(a, b)), NOT(KOR(BOR(a, b), BAND(a, b))))));
}

int Logic3::CTRL(int a, int b) {
	// This "gate" is used nothing more as a catalyst for our adder
	// In truth, we don't even need this method, but it will look neater in the code.
	/* 
	2 2 2
	2 2 0
	2 0 2
	*/
	return (BOR(UNCERTAIN, KOR(KAND(KAND(a, b), KOR(BOR(a, b), BAND(a, b))), NOT(KAND(KAND(a, b), KOR(BOR(a, b), BAND(a, b)))))));
}

void Logic3::ADD(int a, int b, int cin, int& cout, int& sum) {
	sum = SUM(cin, SUM(a, b));
	cout = KOR(REM(a, b), REM(cin, SUM(a, b)));
}

Logic3::~Logic3()
{
}
