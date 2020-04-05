#include <iostream>
#include <cmath>
#include <cstring>
#include "Polynominal.h"
using namespace std;



// constructors and destructor
Polynominal::Polynominal() {
	size = 0;
	coef = nullptr;
}

Polynominal::Polynominal(int size, const double* coef) {
	setCoefficientAll(size, coef);
}

Polynominal::Polynominal(const Polynominal& expression) {
	setCoefficientAll(expression.size, expression.coef);
}

Polynominal::~Polynominal() {
	delete[] this->coef;
	this->coef = nullptr;
}


// member functions
int Polynominal::getSize() const
{
	return size;
}

void Polynominal::setSize(int size) {
	this->size = size;
}

double Polynominal::getCoefficient(int degree) const {
	return coef[degree];
}

void Polynominal::setCoefficient(int power, double num) {
	coef[power] = num;
}

void Polynominal::setCoefficientAll(int size, const double* coef) {
	this->size = size;
	this->coef = new double[size];
	if (coef != nullptr) {
		for (int i = 0; i < size; i++) {
			this->coef[i] = coef[i];
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			this->coef[i] = 0;
		}
	}
}

double Polynominal::calculate(double x) const {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += coef[i] * pow(x, i);
	}
	return sum;
}



// operators
Polynominal Polynominal::operator+(const Polynominal& expression) {
	// whether *this works or not
	Polynominal higherDegree = (this->size > expression.size) ? *this : expression;
	Polynominal lowerDegree = (this->size > expression.size) ? expression : *this;
	Polynominal out = Polynominal(higherDegree);
	for (int i = 0; i < lowerDegree.size; i++) {
		out.coef[i] += lowerDegree.coef[i];
	}
	return out;
}

Polynominal Polynominal::operator-(const Polynominal& expression) {
	Polynominal higherDegree = (this->size > expression.size) ? *this : expression;
	Polynominal lowerDegree = (this->size > expression.size) ? expression : *this;
	Polynominal out = Polynominal(higherDegree);
	for (int i = 0; i < lowerDegree.size; i++) {
		out.coef[i] -= lowerDegree.coef[i];
	}
	return out;
}

Polynominal Polynominal::operator*(const double num) {
	Polynominal out(size, coef);
	for (int i = 0; i < size; i++) {
		out.coef[i] *= num;
	}
	return out;
}

Polynominal Polynominal::operator*(const Polynominal& expression) {
	int newSize = this->size + expression.size - 1;
	Polynominal out(newSize, nullptr);
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < expression.size; j++) {
			out.coef[i + j] += this->coef[i] * expression.coef[j];
		}
	}
	return out;
}

void Polynominal::operator=(const Polynominal& expression) {
	delete[] this->coef;
	this->coef = nullptr;
	setCoefficientAll(expression.size, expression.coef);
}

bool Polynominal::operator==(const Polynominal& expression) {
	bool out = false;
	if (this->size == expression.size) {
		out = true;
		for (int i = 0; i < this->size; i++) {
			out = out && (this->coef[i] == expression.coef[i]);
		}
	}
	return out;
}

bool Polynominal::operator!=(const Polynominal& expression) {
	if (*this == expression)
		return false;
	else
		return true;
}

void Polynominal::operator+=(const Polynominal& expression) {
	if (this->size >= expression.size) { // if so, just add expression's coefficients
		for (int i = 0; i < expression.size; i++) {
			this->coef[i] += expression.coef[i];
		}
	}
	else { // if not, create allocate new memory in heap and substitute if for the result coefficient array
		double* temp = new double[expression.size];
		for (int i = 0; i < this->size; i++) {
			temp[i] = this->coef[i] + expression.coef[i];
		}
		for (int i = this->size; i < expression.size; i++) {
			temp[i] = expression.coef[i];
		}

		delete[] this->coef;
		this->coef = temp;
		temp = nullptr;
		this->size = expression.size;
		return;
	}
}

void Polynominal::operator-=(const Polynominal& expression) { // basically same alogirthm as += operation
	if (this->size >= expression.size) {
		for (int i = 0; i < expression.size; i++) {
			this->coef[i] -= expression.coef[i];
		}
	}
	else {
		double* temp = new double[expression.size];
		for (int i = 0; i < this->size; i++) {
			temp[i] = this->coef[i] - expression.coef[i];
		}
		for (int i = this->size; i < expression.size; i++) {
			temp[i] = -expression.coef[i];
		}

		delete[] this->coef;
		this->coef = temp;
		temp = nullptr;
		this->size = expression.size;
		return;
	}
}

void Polynominal::operator*=(const Polynominal& expression) {
	int newSize = this->size + expression.size - 1;
	double* temp = new double[newSize];
	memset(temp, 0, sizeof(*temp) * newSize);
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < expression.size; j++) {
			temp[i + j] += this->coef[i] * expression.coef[j];
		}
	}
	delete[] this->coef;
	this->coef = temp;
	temp = nullptr;
	this->size = newSize;
	return;
}


// stream functions

ostream& operator<<(ostream& oStream, const Polynominal& expression) {
	for (int i = expression.size - 1; i > -1; i--) {
		if (i == 0) {
			oStream << expression.coef[i];
			break;
		}
		oStream << expression.coef[i] << "x^" << i << " + ";
	}
	return oStream;
}

istream& operator>>(istream& iStream, Polynominal& expression) {
	if (expression.size == 0) {
		int degree;
		cout << "Degree of Polynominal (int) ->";
		cin >> degree;
		expression.size = degree + 1;
		expression.coef = new double[expression.size];
	}
	for (int i = expression.size - 1; i > -1; i--) {
		cout << "coefficient of " << i << "th power term ->";
		double num;
		iStream >> num;
		expression.setCoefficient(i, num);
	}
	return iStream;
}
