#include "stdafx.h"
#include "Logic2.h"

#define FALSE 0
#define TRUE 1


Logic2::Logic2()
{
}

int Logic2::AND(int a, int b) {
	if (a == FALSE) return FALSE;
	if (b == FALSE) return FALSE;
	return TRUE;
}

int Logic2::OR(int a, int b) {
	if (a == TRUE) return TRUE;
	if (b == TRUE) return TRUE;
	return FALSE;
}

int Logic2::XOR(int a, int b) {
	if (a == b) return FALSE;
	return TRUE;
}

void Logic2::ADD(int a, int b, int cin, int &cout, int &sum) {
	sum = (XOR(XOR(a, b), cin));
	cout = (OR(AND(a, b), AND(XOR(a, b), cin)));
}


Logic2::~Logic2()
{
}
