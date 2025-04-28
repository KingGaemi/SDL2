#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ECS/Entity.h"


enum class Cursors{
	Pointer,
	Grab,
	Hover,
	HandPointer

};



class CursorManager {

public:
	CursorManager () {
		init();
	}
	void init();
	void loadCursor(Cursors type);
	void changeCursor(Cursors type);

	Cursors getCurrentCursor(){
		return currentCursor;
	};



	std::shared_ptr<Entity> clickedEntity;
private:
	Cursors currentCursor;
	SDL_Cursor* pointer;
	SDL_Cursor* grab;
	SDL_Cursor* hover;
	SDL_Cursor* handPointer;
};