#include "Game.h"

int main(int argc, char** argv) {
	Game game;
	if (game.Initialize("Sample Text")) {
		game.RunLoop();
	}
	game.Finalize();
	return 0;
}