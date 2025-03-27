#include "Manager/CursorManager.h"
#include <iostream>

void CursorManager::init(){

    loadCursor(Cursors::Pointer);
    loadCursor(Cursors::Grab);
    loadCursor(Cursors::Hover);
    loadCursor(Cursors::HandPointer);

    changeCursor(Cursors::Pointer);
    SDL_ShowCursor(SDL_ENABLE);
}

void CursorManager::changeCursor(Cursors type) {
    switch (type) {
        case Cursors::Pointer: SDL_SetCursor(pointer); 
                    currentCursor = Cursors::Pointer;
            break;
        case Cursors::Grab: SDL_SetCursor(grab); 
                    currentCursor = Cursors::Grab;
            break;
        case Cursors::Hover: SDL_SetCursor(hover);
                    currentCursor = Cursors::Hover;
            break;
        case Cursors::HandPointer: SDL_SetCursor(handPointer);
                    currentCursor = Cursors::HandPointer;
            break;
    }
}


void CursorManager::loadCursor(Cursors type){
    SDL_Surface* cursorSurface;
    switch (type) {
        case Cursors::Pointer: cursorSurface = IMG_Load("res/gfx/UI/cursor/1. Pointer.png"); break;
        case Cursors::Grab: cursorSurface = IMG_Load("res/gfx/UI/cursor/4. Hand Grab.png"); break;
        case Cursors::Hover: cursorSurface = IMG_Load("res/gfx/UI/cursor/3. Hand Hover.png"); break;
        case Cursors::HandPointer: cursorSurface = IMG_Load("res/gfx/UI/cursor/2. Hand Pointer.png"); break;
    }
    if(!cursorSurface){
        printf("Failed to load cursor image: %s\n", IMG_GetError());
    } else {
        switch (type) {
            case Cursors::Pointer: pointer = SDL_CreateColorCursor(cursorSurface, 6, 6) ; break;
            case Cursors::Grab: grab = SDL_CreateColorCursor(cursorSurface, 12, 6); break;
            case Cursors::Hover: hover = SDL_CreateColorCursor(cursorSurface, 12, 6); break;
            case Cursors::HandPointer: handPointer = SDL_CreateColorCursor(cursorSurface, 12, 6); break;
        }
        SDL_FreeSurface(cursorSurface);
    }


}
