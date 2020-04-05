#include <iostream>
#include <cstring>
#include "Cubic.h"
#include "Polynominal.h"
using namespace std;

/* Test
Operations:
	provide inputs and outputs that the program is supposed to put out,
	and then see if the program works correctly by comparing outputs to provided ones.
Stream:
	will be demonstrated by users. so prompt inputs and display output accordingly,
	so users can see how it works by themselves.
*/

// cubic
bool cubicBinary() {
	Cubic c1 = Cubic(1, 2, 3, 4);
	Cubic c2 = Cubic(4, 3, 2, 1);
	Cubic c3, c4, c5, c6;

	// comparision !=
	bool b0 = c1 != c2;

	// add
	c3 = c1 + c2;
	Cubic c7 = Cubic(5, 5, 5, 5);
	bool b1 = c7 == c3;

	// subtract
	c4 = c1 - c2;
	Cubic c8 = Cubic(-3, -1, 1, 3);
	bool b2 = c8 == c4;

	// int multiplication
	c5 = c1 * 2;
	Cubic c9 = Cubic(2, 4, 6, 8);
	bool b3 = c9 == c5;

	// double multiplication
	c6 = c1 * 5.5;
	Cubic c10 = Cubic(1 * 5.5, 2 * 5.5, 3 * 5.5, 4 * 5.5);
	bool b4 = c6 == c10;
	return b0 && b1 && b2 && b3 && b4;
}
bool cubicUnary() {
	Cubic c1 = Cubic(1, 2, 3, 4);
	Cubic c2 = Cubic(4, 3, 2, 1);

	// += 
	Cubic c3 = Cubic(5, 5, 5, 5);
	c1 += c2;
	bool b1 = c1 == c3;

	// -=
	Cubic c4 = Cubic(1, 2, 3, 4);
	c1 -= c2;
	bool b2 = c1 == c4;

	return b1 && b2;
}
bool cubicTest() {
	return cubicBinary() && cubicUnary();
}

//polynominal
bool polynominalBinary() {
	double e1[5] = { 1, 2, 3, 4, 5 };
	double e2[4] = { 4, 3, 2, 1 };
	Polynominal p1(5, e1);
	Polynominal p2(4, e2);
	Polynominal p3, p4, p5;


	// comparison !=
	bool b0 = p1 != p2;

	// add 
	double e3[5] = { 5, 5, 5, 5, 5 };
	Polynominal p6(5, e3);
	p3 = p1 + p2;
	bool b1 = p3 == p6;

	// subtract
	double e4[5] = { -3, -1, 1, 3, 5 };
	Polynominal p7(5, e4);
	p4 = p1 - p2;
	bool b2 = p4 == p7;

	//multiplication polynominal
	double e5[8] = { 4, 11, 20, 30, 40, 26, 14 ,5 };
	Polynominal p8(8, e5);
	p5 = p1 * p2;
	bool b3 = p5 == p8;

	//multiplication double
	double e6[4] = { 8, 6, 4, 2 };
	Polynominal p9(4, e6);
	p5 = p2 * 2;
	bool b4 = p5 == p9;

	return b0 && b1 && b2 && b3 && b4;
}
bool polynominalUnary() {
	double e1[5] = { 1, 2, 3, 4, 5 };
	double e2[4] = { 4, 3, 2, 1 };
	Polynominal p1(5, e1);
	Polynominal p2(4, e2);


	// +=
	double e3[5] = { 5, 5, 5, 5, 5 };
	Polynominal p3(5, e3);
	p1 += p2;
	bool b1 = p1 == p3;

	// -=
	Polynominal p4(5, e1);
	p1 -= p2;
	bool b2 = p1 == p4;

	// *=
	double e4[8] = { 4, 11, 20, 30, 40, 26, 14 ,5 };
	Polynominal p5(8, e4);
	p1 *= p2;
	bool b3 = p1 == p5;

	return b1 && b2 && b3;
}
bool polynominalTest() {
	return polynominalBinary() && polynominalUnary();
}


// stream test
void cubicStream() {
	// input and output
	Cubic c1;
	cin >> c1;
	cout << c1 << endl;

	// calculate cubic expression
	double x;
	cout << "x value ->";
	cin >> x;
	cout << c1.calculate(x);
}
void polynominalStream() {
	// input and output
	Polynominal p1;
	cin >> p1;
	cout << p1 << endl;

	// calculate cubic expression
	double x;
	cout << "x value ->";
	cin >> x;
	cout << p1.calculate(x);
}


int main(void) {
	// cubic test
	cout << "cubic test (success if returns 1)" << endl;
	bool ct = cubicTest();
	cout << ct << endl; //if return 1, it means it works correctly

	// polynominal test
	cout << "polynominal test (success if returns 1)" << endl;
	bool qt = polynominalTest();
	cout << qt << endl; //if return 1, it means it works correctly

	cout << endl;
	cout << "-----" << endl;
	cout << endl;

	// stream test
	cout << "stream test" << endl;
	cout << "cubic" << endl;
	cubicStream();
	cout << endl;
	cout << "polynominal" << endl;
	polynominalStream();
	return 0;
}
