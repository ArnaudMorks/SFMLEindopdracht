#include "Game.h"


int main()
{
	//Initialize strand
	std::srand(static_cast<unsigned>(time(NULL)));		//"srand" = s rand

	//Initialize Game Engine
	Game game;		//game object

	//Game loop
	while (game.running())
	{
		//Update
		game.update();

		//Render
		game.render();

	}



	//End of application
	return 0;

}