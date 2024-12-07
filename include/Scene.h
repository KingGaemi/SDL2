#pragma once
#include <SDL2/SDL.h>
#include "EventQueue.h"


class Renderer;


class Scene
{
public:
	virtual ~Scene();

	virtual void init(Renderer* renderer) = 0;
	virtual void handleEvents(Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(Renderer* renderer) = 0;
};