// void listRenderDrivers() {
//     int numDrivers = SDL_GetNumRenderDrivers();
//     SDL_RendererInfo info;

//     for (int i = 0; i < numDrivers; ++i) {
//         SDL_GetRenderDriverInfo(i, &info);
//         std::cout << "Driver " << i << ": " << info.name << std::endl;
//     }
// }


#include "Game.h"




int main(int argc, char* args[])
{
    
    
	Game game;


    game.init("Game.1.0.1", 1280, 800, false);


	game.run();

    game.clean();







	return 0;


}