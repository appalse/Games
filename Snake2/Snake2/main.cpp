#include "Game.h"
#include <chrono>		/* duration */
#include <thread>

int main()
{
	// play 1 game round
	Game game;
	game.Play();

	std::this_thread::sleep_for(std::chrono::milliseconds(TIMEOUT * 10 * 5));

	return 0;
}
