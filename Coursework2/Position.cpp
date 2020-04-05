#include <iostream>
#include "Position.h"

using namespace std;

Position::Position()
{
	x = 0.0;
	y = 0.0;
}

Position::Position(double ix, double iy)
{
	x = ix;
	y = iy;
}

double Position::Dot(Position p1, Position p2)
{
	double out = p1.x * p2.x + p1.y * p2.y;
	return out;
}

double Position::Dot3(Position p1, Position p2)
{
	double out = p1.x * p2.x + p1.y * p2.y + p1.c * p2.c;
	return out;
}

namespace Templates {
	template<typename T>
	inline T Clamp(T low, T high, T value) {
		if (value < low)
			return low;
		if (value > high)
			return high;
		return value;
	}
}

Position Position::Clamp(const Position low, const Position high, const Position p)
{
	Position out;
	out.x = Templates::Clamp(low.x, high.x, p.x);
	out.y = Templates::Clamp(low.y, high.y, p.y);
	return out;
}

double Position::Length(Position p1)
{
	double disp2 = std::pow(p1.x, 2) + std::pow(p1.y, 2);
	return std::pow(disp2, 0.5);
}

Position Position::Normalize(Position p1)
{
	return Position(p1) / Position::Length(p1);
}

double Position::getAngle(Position p1)
{
	if (p1.y >= 0)
		return std::atan(p1.y / p1.x);
	else
		return -std::atan(p1.y / p1.x);
}

Position Position::displacement(double dis, DIRECTION dir)
{
	int degree = 45 * (int)dir;
	return Position(dis * std::cos(degree), dis * std::sin(degree));
}

Position Position::getLineEqueation(Position p1, Position p2)
{
	Position out, diff = (p2 - p1);
	if (abs(p1.x - p2.x) < DBL_EPSILON) {
		out.x = 1;
		out.y = 0;
		out.c = -p1.x;
	}
	else if (abs(p1.y - p2.y) < DBL_EPSILON) {
		out.x = 0;
		out.y = 1;
		out.c = -p1.y;
	}
	else {
		out.y = 1;
		out.x = -diff.y / diff.x;
		out.c = -(out.x * p1.x + p1.y);
	}

	return out;
}

double Position::DistanceFromLine(Position line, Position p)
{
	return abs(DistanceWithDirection(line, p));
}

double Position::DistanceWithDirection(Position line, Position p)
{
	return Position::Dot3(line, p) / Position::Length(line);
}

Position Position::operator+(Position p)
{
	return Position(x + p.x, y + p.y);
}

Position Position::operator-(Position p)
{
	return Position(x - p.x, y - p.y);
}

Position Position::operator*(double a)
{
	return Position(x * a, y * a);
}

Position Position::operator/(double a)
{
	return Position(x / a, y / a);
}

void Position::operator+=(Position p)
{
	x += p.x;
	y += p.y;
}
void Position::operator-=(Position p)
{
	x -= p.x;
	y -= p.y;
}

void Position::operator=(Position p)
{
	x = p.x;
	y = p.y;
}

bool Position::operator==(Position p)
{
	bool bx = x == p.x;
	bool by = y == p.y;

	return bx && by;
}

ostream& operator<<(ostream& Ostream, const Position& p)
{
	Ostream << "(" << p.x << ", " << p.y << ")";
	return Ostream;
}
