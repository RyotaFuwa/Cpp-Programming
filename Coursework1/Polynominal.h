#pragma once
#include <iostream>
using namespace std;


class Polynominal {
public:
	Polynominal();
	Polynominal(int size, const double* coef = nullptr);
	Polynominal(const Polynominal& expression);
	~Polynominal();

	int getSize() const;
	void setSize(int size);
	double getCoefficient(int degree) const;
	void setCoefficient(int power, double num);
	void setCoefficientAll(int size, const double* coef = nullptr); // nums array must have the same size
	double calculate(double value) const;

	Polynominal operator+(const Polynominal& expression);
	Polynominal operator-(const Polynominal& expression);
	Polynominal operator*(const double num);
	Polynominal operator*(const Polynominal& expression);
	void operator=(const Polynominal& expression);
	bool operator==(const Polynominal& expression);
	bool operator!=(const Polynominal& expression);
	void operator-=(const Polynominal& expression);
	void operator+=(const Polynominal& expression);
	void operator*=(const Polynominal& expression);

	friend ostream& operator<<(ostream& oStream, const Polynominal& expression);
	friend istream& operator>>(istream& iStream, Polynominal& expression);

private:
	int size;
	double* coef;
};
