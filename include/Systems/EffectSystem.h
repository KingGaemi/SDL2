#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Requests.h"
#include "Rect.h"
#include "TextureManager.h"
#include "EffectManager.h"



class Renderer;

class EffectSystem : public System{

public:
	
	EffectSystem(std::shared_ptr<EffectManager> effectManager) : effectManager(effectManager) {}
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

	void floatingEffect(std::shared_ptr<Entity>& entity, float deltaTime);
	// void hpBarControl(std::shared_ptr<Entity>& hpGage, std::shared_ptr<Entity>& player);
	void hpBarControl(std::shared_ptr<Entity>& player);
private:

	std::shared_ptr<EffectManager> effectManager;
	std::shared_ptr<Entity> player;

};