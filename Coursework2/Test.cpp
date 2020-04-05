#include "Test.h"
#include "Piece.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "CollisionDetection.h"

using namespace Collision;

bool TestCollisionExsit()
{
	double x = cos(3.14159265 / 4.0);
	double y = sin(3.14159265 / 4.0);
	double mx = -x;
	double my = -y;
	Position p1(0, 0), p2(2 * x + 0.01, 2 * y + 0.01), p3(2 * x - 0.01, 2 * y - 0.01);
	Position p4(2 - 0.01, 2 - 0.01), p5(2 + 0.01, 2 + 0.01);

	bool b1 = !CircleCircle(p1, p2);
	bool b2 = CircleCircle(p1, p3);

	bool b3 = CircleRectangle(p1, p2);
	bool b4 = RectangleCircle(p1, p2);

	bool b5 = RectangleRectangle(p1, p4);
	bool b6 = !RectangleRectangle(p1, p5);

	return b1 && b2 && b3 && b4 && b5 && b6;
}

bool TestCollisionDetectionWhileMoving()
{
	Trajectory tr;
	tr.start = Position(0.5, 0.5); tr.end = Position(10.5, 10.5);
	tr.startL = Position(0, 1); tr.startR = Position(1, 0); tr.endL = Position(10, 11), tr.endR = Position(11, 10);

	Position p0(1, 4), p1(2, 0.1), p2(5, 1), p3(8, 4), p4(14, 14);

	Position ret0 = TrajectoryCircle(tr, p0);
	bool b0 = ret0.x > 0;
	Position ret1 = TrajectoryCircle(tr, p1);
	bool b1 = ret1.x > 0;
	Position ret2 = TrajectoryCircle(tr, p2);
	bool b2 = ret2.x < 0;
	Position ret3 = TrajectoryRectangle(tr, p3);
	bool b3 = ret3.x < 0;
	Position ret4 = TrajectoryRectangle(tr, p4);
	bool b4 = ret4.x < 0;

	return b0 && b1 && b2 && b3 && b4;
}

