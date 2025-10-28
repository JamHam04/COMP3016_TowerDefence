#include "Game.h"

int main(int argc, char* argv[]) {

	Game game;
	game.Setup();

	while (!game.getGameOver()) {
		game.Input(); // Player Inputs
		game.Logic(); // Game Logic
		game.Render(); // Render map
	}

	return 0;
}