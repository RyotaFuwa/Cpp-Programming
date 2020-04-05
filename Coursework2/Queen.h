#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen();
	Queen(const Board* b);
	Queen(double x, double y);

	void moveAttempt(double dis, DIRECTION dir)	override;
	bool collisionExist(const Piece& p)				override;
	bool collisionDetectWhileMoving(const Piece& p)	override;
};

