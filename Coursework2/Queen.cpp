#include "Queen.h"

Queen::Queen() : Piece()
{
	type = QUEEN;
	shape = CIRCLE;
}

Queen::Queen(const Board* b) : Piece(b)
{
	type = QUEEN;
	shape = CIRCLE;
}

Queen::Queen(double x, double y) : Piece(x, y)
{
	type = QUEEN;
	shape = CIRCLE;
}

void Queen::moveAttempt(double dis, DIRECTION dir)
{
	tmpPos = currentPos + Position::displacement(dis, dir);
}

bool Queen::collisionExist(const Piece& p)
{
	bool col = false;
	switch (p.getShape())
	{
	case CIRCLE:
		col = CircleCircle(currentPos, p.getPos());
		break;
	case RECTANGLE:
		col = CircleRectangle(currentPos, p.getPos());
		break;
	default:
		break;
	}

	if (col)
		tmpPos = currentPos;
	return col;
}

bool Queen::collisionDetectWhileMoving(const Piece& p)
{

	// calcuate trajectory of circle piece (Rectangle)
	Trajectory tr;
	tr.start = currentPos;
	tr.end = tmpPos;

	Position diff = tmpPos - currentPos;
	double angle = Position::getAngle(diff);
	double angle1 = angle - 3.1415926535 / 2.0;
	double angle2 = angle + 3.1415926535 / 2.0;

	tr.startR = Position(currentPos.x + cos(angle1), currentPos.y + sin(angle1));
	tr.startL = Position(currentPos.x + cos(angle2), currentPos.y + sin(angle2));
	tr.endR = Position(tmpPos.x + cos(angle1), tmpPos.y + sin(angle1));
	tr.endL = Position(tmpPos.x + cos(angle2), tmpPos.y + sin(angle2));

	Position collisionPoint;
	SHAPE s = p.getShape();
	if (s == CIRCLE)
		collisionPoint = TrajectoryCircle(tr, p.getPos());
	else if (s == RECTANGLE)
		collisionPoint = TrajectoryRectangle(tr, p.getPos());
	else
		collisionPoint = Position(-1, -1);

	if (collisionPoint.x < 0) {
		return false;
	}
	else {
		tmpPos = collisionPoint;
		return true;
	}
}
