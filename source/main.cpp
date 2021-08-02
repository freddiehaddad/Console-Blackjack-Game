// ------------------------------------------------------------ Project Headers
#include "Game.h"

// ------------------------------------------------------------ Library Headers
#include <iostream>

// ---------------------------------------------------------------- Entry Point
int main()
{
	std::cout << "Welcome to Console Blackjack!" << std::endl;

	Game game;
	game.Start();

	std::cout << "Thanks for playing!" << std::endl;

	return 0;
}
