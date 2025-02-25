#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"

class EffectSystem : public System{

public:
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

	void floatingEffect(std::shared_ptr<Entity>& entity, float deltaTime);
	// void hpBarControl(std::shared_ptr<Entity>& hpGage, std::shared_ptr<Entity>& player);
	void hpBarControl(std::shared_ptr<Entity>& player);
private:
		
	std::shared_ptr<Entity> player;
	std::shared_ptr<Entity> hpGage;

};