#pragma once

#include "ECS/Component"
#include <string>





class AttackComponent : public Component{


public:

	std::string weaponName;
	void init() override;
	void update() override;


	~AttackComponent();



private:



}