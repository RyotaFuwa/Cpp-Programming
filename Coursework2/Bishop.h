#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop();
	Bishop(const Board* b);
	Bishop(double x, double y);

	void moveAttempt(double dis, DIRECTION dir) override;
	bool collisionExist(const Piece& p)				override;
	bool collisionDetectWhileMoving(const Piece& p)	override;
};

