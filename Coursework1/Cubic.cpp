#include <iostream>
#include <cmath>
#include "Cubic.h"
using namespace std;


Cubic::Cubic(const Cubic& expression) {
	for (int i = 0; i < 4; i++) {
		coef[i] = expression.coef[i];
	}
}

Cubic::Cubic(double c3, double c2, double c1, double c0) {
	coef[3] = c3;
	coef[2] = c2;
	coef[1] = c1;
	coef[0] = c0;
}

//member functions
double Cubic::getCoefficient(int power) const {
	return coef[power];
}
void Cubic::setCoefficient(int power, double value) {
	this->coef[power] = value;
}
double Cubic::calculate(double x) const {
	double sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += this->coef[i] * pow(x, i);
	}
	return sum;
}

//operator functions
void Cubic::operator=(const Cubic& expression) {
	for (int i = 0; i < 4; i++) {
		this->coef[i] = expression.coef[i];
	}
}
Cubic Cubic::operator+(const Cubic& expression) {
	Cubic out = Cubic(*this);
	for (int i = 0; i < 4; i++) {
		out.coef[i] += expression.coef[i];
	}
	return out;
}
Cubic Cubic::operator-(const Cubic& expression) {
	Cubic out = Cubic(*this);
	for (int i = 0; i < 4; i++) {
		out.coef[i] -= expression.coef[i];
	}
	return out;
}
Cubic Cubic::operator*(double num) {
	Cubic out = Cubic(*this);
	for (int i = 0; i < 4; i++) {
		out.coef[i] *= num;
	}
	return out;
}
Cubic Cubic::operator*(int num) {
	Cubic out = Cubic(*this);
	for (int i = 0; i < 4; i++) {
		out.coef[i] *= num;
	}
	return out;
}
bool Cubic::operator==(const Cubic& expression) {
	bool out = true;
	for (int i = 0; i < 4; i++) {
		out = out && (this->coef[i] == expression.coef[i]);
	}
	return out;
}
bool Cubic::operator!=(const Cubic& expression) {
	if (*this == expression)
		return false;
	else
		return true;
}
void Cubic::operator-=(const Cubic& expression) {
	for (int i = 0; i < 4; i++) {
		this->coef[i] -= expression.coef[i];
	}
	return;
}
void Cubic::operator+=(const Cubic& expression) {
	for (int i = 0; i < 4; i++) {
		this->coef[i] += expression.coef[i];
	}
	return;
}

// stream function
ostream& operator<<(ostream& oStream, const Cubic& expression) {
	for (int i = 3; i > -1; i--) {
		if (i == 0) {
			oStream << expression.getCoefficient(0);
			break;
		}
		oStream << expression.getCoefficient(i) << "x^" << i << " + ";
	}
	return oStream;
}
istream& operator>>(istream& iStream, Cubic& expression) {
	// input coeff from 3 to 0
	double value;
	for (int i = 3; i > -1; i--) {
		std::cout << "coefficient of " << i << "th power term ->";
		iStream >> value;
		expression.setCoefficient(i, value);
	}
	return iStream;
}