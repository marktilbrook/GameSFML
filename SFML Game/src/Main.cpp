#include "Game.h"

int main(int argc, char** argv[]) {
	Game game; //creating game object

	while (!game.GetWindow()->IsDone())
	{
		//game loop
		
		game.Update();
		game.Render();
		game.RestartClock();
	}
}
	
