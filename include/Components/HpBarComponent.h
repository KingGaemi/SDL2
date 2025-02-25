#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"

class HpBarComponent : public Component {

public:
	HpBarComponent(std::shared_ptr<Entity> hpGage, std::shared_ptr<Entity> hpFrame) : hpGage(hpGage), hpFrame(hpFrame) {}

	float percentage;
	std::string gageTextureId = "hp_bar_gage";
	std::string frameTextureId = "hp_bar_frame";
	std::size_t type = 1;
	std::shared_ptr<Entity> hpGage, hpFrame;



private:

};