// ------------------------------------------------------------ Project Headers
#include "Game.h"

// ------------------------------------------------------------ Library Headers
#include <iostream>

// ---------------------------------------------------------------- Entry Point
int main()
{
	std::cout << "Welcome to Console" << std::endl;
	std::cout
		<< "__________.__                 __         __               __    "
		<< std::endl;
	std::cout
		<< "\\______   \\  | _____    ____ |  | __    |__|____    ____ |  | __"
		<< std::endl;
	std::cout
		<< " |    |  _/  | \\__  \\ _/ ___\\|  |/ /    |  \\__  \\ _/ ___\\|  |/ /"
		<< std::endl;
	std::cout
		<< " |    |   \\  |__/ __ \\\\  \\___|    <     |  |/ __ \\\\  \\___|    < "
		<< std::endl;
	std::cout
		<< " |______  /____(____  /\\___  >__|_ \\/\\__|  (____  /\\___  >__|_ \\"
		<< std::endl;
	std::cout
		<< "        \\/          \\/     \\/     \\/\\______|    \\/     \\/     \\/"
		<< std::endl;

	Game game;
	game.Start();

	std::cout << std::endl << "Thanks for playing!" << std::endl;

	return 0;
}
