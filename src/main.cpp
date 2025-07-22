#define SDL_MAIN_HANDLED
#include <iostream>
#include "Game.h"





int main(int argc, char* args[])
{   

	
	Game game;

	// 게임 이름, 화면 가로, 높이, 전체화면 여부
    game.init("Game.1.0.1", 1280, 800, false);

	game.run();

    game.clean();

	return 0;

}