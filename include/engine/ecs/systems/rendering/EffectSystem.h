#pragma once

#include "engine/ecs/core/System.h"
#include "engine/ecs/core/Entity.h"
#include "engine/event/Requests.h"
#include "engine/math/Rect.h"
#include "TextureManager.h"
#include "EffectManager.h"



class Renderer;

class EffectSystem : public System{

public:
	
	EffectSystem(std::shared_ptr<EffectManager> effectManager) : effectManager(effectManager) {}
	void update(float deltaTime) override;

	void floatingEffect(std::shared_ptr<Entity>& entity, float deltaTime);
	// void hpBarControl(std::shared_ptr<Entity>& hpGage, std::shared_ptr<Entity>& player);
	void hpBarControl(std::shared_ptr<Entity>& player);
	void ShakeEffect(std::shared_ptr<Entity>& entity, float deltaTime);
	void itemShadowEffect(std::shared_ptr<Entity>& entity);
	void damageTextEffect(std::shared_ptr<Entity>& entity);
private:

	std::shared_ptr<EffectManager> effectManager;
	std::shared_ptr<Entity> player;

};