#pragma once


class Logic3
{
public:
	Logic3();

	static int KAND(int a, int b);    // Kleene AND
	static int KOR(int a, int b);     // Kleene OR
	static int TAND(int a, int b);    // Ternary NAND
	static int TOR(int a, int b);     // Ternary Inverted NOR
	static int BAND(int a, int b);    // Binary NAND
	static int BOR(int a, int b);     // Binary Inverted NOR

	static int NOT(int a);

	static int REM(int a, int b);  // method for calculating the remainder of a + b
	static int SUM(int a, int b);  // method for calculating (a + b) % 3
	static int CTRL(int a, int b); // the "control" method. This is just a means to acheive the SUM "gate"

	// and now, for the adder itself

	static void ADD(int a, int b, int cin, int& cout, int& sum);
	static int ternaryConversion(int decimalNum); // method to convert generated decimal number into ternary

	~Logic3();
};
