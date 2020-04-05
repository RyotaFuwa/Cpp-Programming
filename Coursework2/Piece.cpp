#include "Piece.h"
#include <cmath>
#include <string>


Piece::Piece()
{
}

Piece::Piece(const Board* b)
{
	currentPos.x = rand() % (int)b->width;
	currentPos.y = rand() % (int)b->height;
}

Piece::Piece(double x, double y) : currentPos(x, y) {}
Piece::Piece(Position p) : currentPos(p) {}

Piece::~Piece()
{
}

string Piece::displayShape() const
{
	switch (type) {
	case PIECE:
		return "Piece";
		break;
	case QUEEN:
		return "Queen";
		break;
	case BISHOP:
		return "Bishop";
		break;
	case ROOK:
		return "Rook";
		break;
	default:
		return "";
		break;
	}
}

void Piece::moveAttempt(double dis, DIRECTION dir)
{
	int degree = 45 * (int)dir;
	tmpPos = currentPos + Position(dis * std::cos(degree), dis * std::sin(degree));
}

bool Piece::outOfBoard(const Board* b)
{
	bool out = false;
	if (tmpPos.x < 0)
		out = true; tmpPos.x = 0;
	if (tmpPos.y < 0)
		out = true; tmpPos.y = 0;
	if (tmpPos.x > b->width)
		out = true; tmpPos.x = b->width;
	if (tmpPos.y > b->height)
		out = true; tmpPos.y = b->height;

	return out;
}

bool Piece::operator==(Piece& p)
{
	bool btype = type == p.type;
	bool bpos = currentPos == p.currentPos;
	return btype && bpos;
}

void Piece::operator=(Piece& p)
{
	shape = p.shape;
	currentPos = p.currentPos;
	tmpPos = p.tmpPos;
}

ostream& operator<<(ostream& Ostream, const Piece& p)
{
	string name = p.displayShape();
	Ostream << name << p.currentPos << ": captured = " << p.capture;
	return Ostream;
}
