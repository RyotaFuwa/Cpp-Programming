#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook();
	Rook(const Board* b);
	Rook(double x, double y);

	void moveAttempt(double dis, DIRECTION dir) override;
	bool collisionExist(const Piece& p)				override;
	bool collisionDetectWhileMoving(const Piece& p)	override;
};

