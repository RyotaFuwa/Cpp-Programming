#pragma once
#include <iostream>
#include "Position.h"
#include "CollisionDetection.h"

using namespace std;
using namespace Collision;

enum TYPE {
	PIECE,
	QUEEN,
	BISHOP,
	ROOK
};

enum SHAPE {
	CIRCLE,
	RECTANGLE,
	UNKNOWN
};

struct Board {
	Board(double w, double h) : width(w), height(h) {
		length = (height > width) ? height : width;
	}
	int width;
	int height;
	int length;

};

class Piece {
public:
	Piece();
	Piece(const Board* b);
	Piece(double x, double y);
	Piece(Position p);
	~Piece();

	Position getPos() const { return currentPos; }
	Position getTmpPos() const { return tmpPos; }
	TYPE getType() const { return type; }
	SHAPE getShape() const { return shape; }
	string displayShape() const;

	void setPos(Position p) { currentPos = p; }
	void setShape(SHAPE s) { shape = s; }
	void killOne() { capture++; }
	int	getCapture() { return capture; }

	virtual void moveAttempt(double dis, DIRECTION dir) = 0;
	void move() { currentPos = tmpPos; }

	virtual bool collisionExist(const Piece& p) = 0;				 // update tmpPos if there is already collision between them, and slide itself.
	virtual bool collisionDetectWhileMoving(const Piece& p) = 0;	 // update tmpPos if collision is detected on its way.
	bool outOfBoard(const Board* b);								 // update tmpPos in order not to fall from the board

	bool operator==(Piece& p);
	void operator=(Piece& p);
	friend ostream& operator<<(ostream& Ostream, const Piece& p);

protected:
	TYPE type = PIECE;
	SHAPE shape = UNKNOWN;

	Position currentPos, tmpPos;
	int capture = 0;
};

