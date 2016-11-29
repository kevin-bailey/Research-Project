#pragma once


class Logic2
{
public:
	Logic2();

	static int AND(int a, int b);	// Boolean AND
	static int OR(int a, int b);	// Boolean OR
	static int XOR(int a, int b);	// Boolean Exclusive OR


	static void ADD(int a, int b, int cin, int &cout, int &sum);
	static int binaryConversion(int decimalNum);

	~Logic2();
};

