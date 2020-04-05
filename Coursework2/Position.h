#pragma once
#include <cmath>
#include <iostream>

using namespace std;

enum DIRECTION {
	EAST = 0,
	NORTHEAST,
	NORTH,
	NORTHWEST,
	WEST,
	SOUTHWEST,
	SOURTH,
	SOURTHEAST
};

struct Position
{
	double x;
	double y;
	double c = 1;
	Position();
	Position(double ix, double iy);

	static double Dot(Position p1, Position p2);
	static double Dot3(Position p1, Position p2);
	static Position Clamp(const Position low, const Position high, const Position p);
	static double Length(Position p1);
	static Position Normalize(Position p1);
	static double getAngle(Position p1);
	static Position displacement(double dis, DIRECTION dir);
	static Position getLineEqueation(Position p1, Position p2);
	static double DistanceFromLine(Position line, Position p);
	static double DistanceWithDirection(Position line, Position);

	Position operator+(Position p);
	Position operator-(Position p);
	Position operator*(double a);
	Position operator/(double a);
	void operator+=(Position p);
	void operator-=(Position p);
	void operator=(Position p);
	bool operator==(Position p);
	friend ostream& operator<<(ostream& Ostream, const Position& p);
};
