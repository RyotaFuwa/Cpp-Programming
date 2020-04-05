#include <iostream>
#include <ctime>
#include <vector>
#include "Test.h"
#include "Game.h"

int main()
{
	/*
	std::cout << "Collision Test: " << TestCollisionDetectionWhileMoving() && TestCollisionExsit(); // if 1, it works.
	std::cout << std::endl;
	*/

	Board* b = new Board(500, 500);
	int iteration = 200;
	int initNum = 400;
	Game gameInstance = Game(b, iteration, initNum);

	gameInstance.setPiecesRandomly();
	gameInstance.play();

	std::cout << "*******Game Result*********" << std::endl;
	std::cout << gameInstance;
	std::cout << std::endl;
	std::cout << "*******Show Stats*********" << std::endl;
	gameInstance.showStats();

	delete b;
	b = nullptr;
	return 0;
}


