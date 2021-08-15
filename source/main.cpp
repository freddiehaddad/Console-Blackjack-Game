// ------------------------------------------------------------ Project Headers
#include "Game.h"

// ------------------------------------------------------------ Library Headers
#include <iostream>

// -------------------------------------------------------- Function Prototypes
static void DrawBlackjack();

// ---------------------------------------------------------------- Entry Point
int main()
{
	std::cout << "Welcome to Console" << std::endl;

	DrawBlackjack();

	Game game;
	game.Start();

	std::cout << std::endl << "Thanks for playing!" << std::endl;

	return 0;
}

// ------------------------------------------------------- Function Definitions
static void DrawBlackjack()
{
	std::cout
		<< "__________.__                 __         __               "
		   "__    \n\\______   \\  | _____    ____ |  | __    |__|____"
		   "    ____ |  | __\n |    |  _/  | \\__  \\ _/ ___\\|  |/ / "
		   "   |  \\__  \\ _/ ___\\|  |/ /\n |    |   \\  |__/ __ \\\\"
		   "  \\___|    <     |  |/ __ \\\\  \\___|    < \n |______  /"
		   "____(____  /\\___  >__|_ \\/\\__|  (____  /\\___  >__|_ \\"
		   "\n        \\/          \\/     \\/     \\/\\______|    \\/"
		   "     \\/     \\/\n";
}
