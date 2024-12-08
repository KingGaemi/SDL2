#pragma once
#include <SDL2/SDL.h>
#include "EventQueue.h"
#include "TextureManager.h"
#include "Renderer.h"



class Scene
{
public:
	using ChangeSceneCallback = std::function<void(const std::string&)>;
	Scene(ChangeSceneCallback callback) : changeSceneCallback(callback) {}
	virtual ~Scene();

	virtual void init(Renderer* renderer) = 0;
	virtual void handleEvents(Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(Renderer* renderer) = 0;
    
protected:
	ChangeSceneCallback changeSceneCallback;
};