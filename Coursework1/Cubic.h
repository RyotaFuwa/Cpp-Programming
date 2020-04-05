#pragma once
#include <iostream>
using namespace std;



class Cubic {
public:
	Cubic(double c3 = 0, double c2 = 0, double c1 = 0, double c0 = 0);
	Cubic(const Cubic& expression);

	double getCoefficient(int power) const;
	void setCoefficient(int power, double value);
	double calculate(double x) const;

	void operator=(const Cubic& expression);
	Cubic operator+(const Cubic& expression);
	Cubic operator-(const Cubic& expression);
	Cubic operator*(double num);
	Cubic operator*(int num);
	bool operator==(const Cubic& expression);
	bool operator!=(const Cubic& expression);
	void operator-=(const Cubic& expression);
	void operator+=(const Cubic& expression);

private:
	double coef[4];
};



ostream& operator<<(ostream& oStream, const Cubic& expression);
istream& operator>>(istream& iStream, Cubic& expression);
