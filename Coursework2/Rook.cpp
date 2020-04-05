#include "Rook.h"

Rook::Rook() : Piece()
{
	type = ROOK;
	shape = RECTANGLE;
}

Rook::Rook(const Board* b) : Piece(b)
{
	type = ROOK;
	shape = RECTANGLE;
}

Rook::Rook(double x, double y) : Piece(x, y)
{
	type = ROOK;
	shape = RECTANGLE;
}

void Rook::moveAttempt(double dis, DIRECTION dir)
{
	int direction = dir;
	direction = direction / 2;
	DIRECTION d = (DIRECTION)direction;
	tmpPos = currentPos + Position::displacement(dis, d);
}

bool Rook::collisionExist(const Piece& p)
{
	bool col = false;
	switch (p.getShape())
	{
	case CIRCLE:
		col = RectangleCircle(currentPos, p.getPos());
		break;
	case RECTANGLE:
		col = RectangleRectangle(currentPos, p.getPos());
		break;
	default:
		break;
	}

	if (col)
		tmpPos = currentPos;
	return col;
}

bool Rook::collisionDetectWhileMoving(const Piece& p)
{

	// calculating trajectory of rectangle piece is usually different, but rook only moves horizntally or vertically,
	// so the same implimentation as circle pieces is applicable here.
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
	if (p.getShape() == CIRCLE)
		collisionPoint = TrajectoryCircle(tr, p.getPos());
	else if (p.getShape() == RECTANGLE)
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
