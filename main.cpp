#include "Game.h"

int main (int argc, char *argv[])
{
	srand(timeGetTime());
	Game game;

	return game.GameLoop();
}
