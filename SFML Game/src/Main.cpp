#include "Game.h"

int main(int argc, char** argv[]) {
	Game game; //creating game object

	while (!game.GetWindow()->IsDone())
	{
		//game loop
		game.HandleInput();
		game.Update();
		game.Render();
	}
}
	
