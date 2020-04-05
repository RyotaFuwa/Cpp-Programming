#include <algorithm>
#include "CollisionDetection.h"

bool Collision::CircleCircle(Position pos1, Position pos2)
{
	double len = Position::Length(pos2 - pos1);

	return len <= 2; // since radius of circle is always 1
}

bool Collision::RectangleRectangle(Position pos1, Position pos2)
{
	Position diff = pos2 - pos1;
	return abs(diff.x) <= 2 && abs(diff.y) <= 2.0f;
}

bool Collision::RectangleCircle(Position pos1, Position pos2)
{
	Position nearestEdge;
	nearestEdge = Position::Clamp(pos1 - Position(1.0, 1.0), pos1 + Position(1.0, 1.0), pos2);
	return Position::Length(nearestEdge - pos2) < 1.0f;
}

bool Collision::CircleRectangle(Position pos1, Position pos2)
{
	return RectangleCircle(pos2, pos1);
}

Position Collision::TrajectoryCircle(Trajectory tr, Position p)
{
	Position bottomLine = Position::getLineEqueation(tr.startL, tr.startR);
	Position upperLine = Position::getLineEqueation(tr.endL, tr.endR);

	double len1 = Position::Length(tr.startL - tr.endL);
	bool check1 = Position::DistanceFromLine(bottomLine, p) <= len1 && Position::DistanceFromLine(upperLine, p) <= len1; // see if point is between start and end or not

	if (check1) {
		tr.Wider(1.0);
		Position lSideLine = Position::getLineEqueation(tr.startL, tr.endL);
		Position rSideLine = Position::getLineEqueation(tr.startR, tr.endR);
		double len2 = Position::Length(tr.startL - tr.startR); // this is always 4 though
		bool check2 = Position::DistanceFromLine(lSideLine, p) <= len2;
		bool tst = Position::DistanceFromLine(rSideLine, p) <= len2; // see if it touches to the trajectroy box

		if (check2)
			return Position::Normalize(tr.end - tr.start) * Position::DistanceFromLine(bottomLine, p); // approximately the new position will be point inside trajectory just next to the collision point
	}

	return Position(-1, -1);
}

Position Collision::TrajectoryRectangle(Trajectory tr, Position p)
{
	Position bottomLine = Position::getLineEqueation(tr.startL, tr.startR);
	Position upperLine = Position::getLineEqueation(tr.endL, tr.endR);
	Position lSideLine = Position::getLineEqueation(tr.startL, tr.endL);
	Position rSideLine = Position::getLineEqueation(tr.startR, tr.endR);

	double len1 = Position::Length(tr.startL - tr.endL);
	bool check1 = Position::DistanceFromLine(bottomLine, p) >= len1 && Position::DistanceFromLine(upperLine, p) >= len1; // see if point is between start and end or not

	if (check1) {
		double len2 = Position::Length(tr.startL - tr.startR); // this is always 4 though
		bool check2 = Position::DistanceFromLine(lSideLine, p + Position(1, 1)) >= len2 && Position::DistanceFromLine(rSideLine, p + Position(1, 1)) >= len2; // see if it touches to the trajectroy box
		check2 = check2 || Position::DistanceFromLine(lSideLine, p + Position(-1, 1)) >= len2 && Position::DistanceFromLine(rSideLine, p + Position(-1, 1)) >= len2; // see if it touches to the trajectroy box
		check2 = check2 || Position::DistanceFromLine(lSideLine, p + Position(-1, -1)) >= len2 && Position::DistanceFromLine(rSideLine, p + Position(-1, -1)) >= len2; // see if it touches to the trajectroy box
		check2 = check2 || Position::DistanceFromLine(lSideLine, p + Position(1, -1)) >= len2 && Position::DistanceFromLine(rSideLine, p + Position(1, -1)) >= len2; // see if it touches to the trajectroy box

		if (check1 && check2)
			return Position::Normalize(tr.end - tr.start) * Position::DistanceFromLine(bottomLine, p);

	}

	return Position(-1, -1);
}

