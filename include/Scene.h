#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "EventQueue.h"
#include "TextureManager.h"

class Renderer;


class Scene
{
public:
	using ChangeSceneCallback = std::function<void(const std::shared_ptr<Scene>&)>;
	Scene(const std::string scenename, ChangeSceneCallback callback) : name(scenename) , changeSceneCallback(callback) {}
	virtual ~Scene();

	virtual void init(Renderer* renderer) = 0;
	virtual void handleEvents(Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(Renderer* renderer) = 0;

    std::string getName() const {return name;}
    
protected:
	std::string name;
	ChangeSceneCallback changeSceneCallback;
};