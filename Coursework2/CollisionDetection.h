#pragma once
#include "Position.h"

namespace Collision {
	struct Trajectory {

		void Wider(float len) {
			Position diff = startL - startR;
			Position diffNormalized = Position::Normalize(diff);
			startL += diffNormalized * len;
			startR -= diffNormalized * len;
			endL += diffNormalized * len;
			endR -= diffNormalized * len;
		}
		Position start;
		Position end;
		Position startR;
		Position startL;
		Position endR;
		Position endL;
	};

	bool CircleCircle(Position p1, Position p2);
	bool RectangleRectangle(Position p1, Position p2);
	bool RectangleCircle(Position p1, Position p2);
	bool CircleRectangle(Position p1, Position p2);

	Position TrajectoryCircle(Trajectory tr, Position p); // return Position(-1, -1) if no collision.
	Position TrajectoryRectangle(Trajectory tr, Position p); // return Position(-1, -1) if no collision.
}



