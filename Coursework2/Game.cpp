#include "Game.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

Game::Game(Board* b, int iter, int numP) : board(b), iteration(iter), initNum(numP), dead_count(0) {}
Game::~Game() {
	for (auto p : pieces) {
		delete p;
	}
}

void Game::setBoard(Board* b) { board = b; }
Board* Game::getBoard() { return board; }
void Game::reSetGame() {
	for (auto p : pieces) {
		delete p;
	}
	pieces.clear();
}
void Game::setIteration(int i) { iteration = i; }
int Game::getIteration() const { return iteration; }

void Game::setPiecesRandomly() {
	for (int i = 0; i < initNum; i++) {
		int random = rand() % 3;
		switch (random) {
		case 0:
			pieces.push_back(new Bishop(board));
			break;
		case 1:
			pieces.push_back(new Rook(board));
			break;
		case 2:
			pieces.push_back(new Queen(board));
			break;
		default:
			break;
		}
	}
}

void Game::setPiece(TYPE type, double x, double y) {
	switch (type) {
	case BISHOP:
		pieces.push_back(new Bishop(x, y));
		break;
	case ROOK:
		pieces.push_back(new Rook(x, y));
		break;
	case QUEEN:
		pieces.push_back(new Queen(x, y));
		break;
	default:
		break;
	}
}

void Game::kill(int index) { pieces.erase(pieces.begin() + index); }

int Game::getSurvivorNum() {
	return pieces.size();
}

void Game::play() {
	for (int i = 0; i < iteration; i++) {
		if (getSurvivorNum() < 3) {
			break;
		}

		int moveIndex = rand() % pieces.size(); // randomly choose a piece
		Piece* pMove = pieces[moveIndex];
		double distance = 0.5 * (rand() % board->length);
		int dirNum = rand() % 8;
		pMove->moveAttempt(distance, (DIRECTION)dirNum);
		pMove->outOfBoard(board);

		Piece* killer = nullptr;
		int killee = pieces.size();
		for (int otherIndex = 0; otherIndex != pieces.size(); otherIndex++) { // collision check
			if (moveIndex == otherIndex) {
				continue;
			}
			Piece* pOther = pieces[otherIndex];
			if (pMove->collisionExist(*pOther)) {
				killer = pOther;
				killee = moveIndex;
				break;
			}
			if (pMove->collisionDetectWhileMoving(*pOther)) {
				killer = pMove;
				killee = otherIndex;
			}
		}
		if (killee < pieces.size()) {
			killer->killOne();
			kill(killee);
		}
		pMove->move();
	}
}

void Game::showStats() {
	int bishopCount = 0;
	int bishopCapture = 0;
	int rookCount = 0;
	int rookCapture = 0;
	int queenCount = 0;
	int queenCapture = 0;

	for (Piece* p : pieces) {
		TYPE type = p->getType();
		switch (type) {
		case BISHOP:
			bishopCount++;
			bishopCapture += p->getCapture();
			break;
		case ROOK:
			rookCount++;
			rookCapture += p->getCapture();
			break;
		case QUEEN:
			queenCount++;
			queenCapture += p->getCapture();
			break;
		default:
			break;
		}
	}
	std::cout << "---" << "Survivors: " << getSurvivorNum() << "---" << std::endl;
	std::cout << "Bishop Survived: " << bishopCount << std::endl;
	std::cout << "Rook   Survived: " << rookCount << std::endl;
	std::cout << "Queen  Survived: " << queenCount << std::endl;

	std::cout << "---" << "Piece Score: " << initNum - pieces.size() << "---" << std::endl;
	std::cout << "Bishop Score: " << bishopCapture << std::endl;
	std::cout << "Rook   Score: " << rookCapture << std::endl;
	std::cout << "Queen  Score: " << queenCapture << std::endl;
}

ostream& operator<<(ostream& Ostream, const Game& g) {
	for (const Piece* p : g.pieces) {
		Ostream << *p << std::endl;
	}
	return Ostream;
}

