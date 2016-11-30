#include "stdafx.h"
#include <iostream>
#include "Logic2.h"
#include "Logic3.h"
#include "Processor.h"
#include <vector>
#include <cmath>


using namespace std;

// Constants
const int ADDITIONS = 1000000;	// number of instructions to be performed
const int ITERATIONS = 1;      // number of times to repeat the set of instructions
						        // too many randomly generated nums crashes the application :(

// Functions
void convert(int numA, int numB);	// converts decimal to binary or ternary

// Variables
int digitCount;			// Number of digits generated for each number
double startTime;
double endTime;
int conversionVar;		// 3 indicates Ternary, 2 indicates Binary
int decimalArrayA[ADDITIONS];
int decimalArrayB[ADDITIONS];
int carry = 0;
int sum = 0;

// Objects
Processor processor;	// This will be used to measure CPU time

vector<vector<int>> convertedSetA;
vector<vector<int>> convertedSetB;

vector<int> convertedNumberA;
vector<int> convertedNumberB;

int main() {
	cout << "Enter digit count: ";
	cin >> digitCount;
	cout << "\nGenerating sets of decimal numbers...";

	int num1; // upper bound for generated numbers
	int num2; // lower bound

	// generate numbers here
	for (int i = 0; i < ADDITIONS; i++) {
		num1 = (pow(10, digitCount) - 1);
		num2 = (pow(10, digitCount - 1));
		decimalArrayA[i] = rand() % num1 + num2;
		num1 = (pow(10, digitCount) - 1);
		num2 = (pow(10, digitCount - 1));
		decimalArrayB[i] = rand() % num1 + num2;
	}

	cout << " done!";
	do {
		cout << "\n\nMeasure in ternary or binary (enter 3 or 2): ";
		cin >> conversionVar;
		cout << "\nConverting decimal sets into ";
		if (conversionVar == 2) cout << "binary...";
		else if (conversionVar == 3) cout << "ternary...";
		else return 0;

		// convert numbers here
		for (int i = 0; i < ADDITIONS; i++) {
			convert(decimalArrayA[i], decimalArrayB[i]);
		}

		cout << " done!\n\nAdding numbers...";
		startTime = processor.getCPUTime();


		if (conversionVar == 3) {
			for (int k = 0; k < ITERATIONS; k++) {
				for (int i = 0; i < ADDITIONS; i++) {
					carry = 0;
					sum = 0;
					for (int j = 0; j < convertedSetA[i].size(); j++) {
						Logic3::ADD(convertedSetA[i][j], convertedSetB[i][j], carry, carry, sum);
					}
				}
			}
		}
		else {
			for (int k = 0; k < ITERATIONS; k++) {
				for (int i = 0; i < ADDITIONS; i++) {
					carry = 0;
					sum = 0;
					for (int j = 0; j < convertedSetA[i].size(); j++) {
						Logic2::ADD(convertedSetA[i][j], convertedSetB[i][j], carry, carry, sum);
					}
				}
			}
		}

		endTime = processor.getCPUTime();
		cout << " done!\n\nTotal time elapsed for "
			<< (ADDITIONS * ITERATIONS) << " additions is "
			<< (endTime - startTime) * 1000
			<< " CPU ticks.\n\n";
		convertedSetA.clear();
		convertedSetB.clear();
	} while (1);

	return 0;
}


void convert(int numA, int numB) {
	// create two temporary vectors
	vector<int> temp1;
	vector<int> temp2;

	// converted number is stored in reverse order
	while (numA > 0) {
		temp1.push_back(numA % conversionVar);
		numA /= conversionVar;
	}

	// Then do the same for B
	while (numB > 0) {
		temp2.push_back(numB % conversionVar);
		numB /= conversionVar;
	}
	
	// Add zeroes so the numbers' size are even (1001 + 0110)
	while (temp1.size() > temp2.size()) temp2.push_back(0);
	while (temp1.size() < temp2.size()) temp1.push_back(0);

	// Afterwards, store in global vector in proper order
	for (int i = 0; i < temp1.size(); i++) {
		convertedNumberA.push_back(temp1[i]);
		convertedNumberB.push_back(temp2[i]);
	}

	convertedSetA.push_back(convertedNumberA);
	convertedSetB.push_back(convertedNumberB);
	convertedNumberA.clear();
	convertedNumberB.clear();
}