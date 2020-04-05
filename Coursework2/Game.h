#pragma once
#include <vector>
#include "Piece.h"

class Game {
public:
	Game(Board* b, int iter, int numP);
	~Game();
	void setBoard(Board* b);
	Board* getBoard();
	void reSetGame();

	void setIteration(int i);
	int getIteration() const;
	void setPiecesRandomly();
	void setPiece(TYPE type, double x, double y);

	void kill(int index);
	int getSurvivorNum();

	void play();
	void showStats();
	friend ostream& operator<<(ostream& Ostream, const Game& g);

private:
	Board* board;
	std::vector<Piece*> pieces;
	int iteration;
	int initNum;
	int dead_count;
};


