#pragma once
#include "ECS/Component.h"

struct Ability{
	std::string abilityName;
	int abilityNumber;
	int abilityId;
	int abilityLevel;
	float cooldownTime;
	std::string iconTextureId;
	bool isPassive;
};


class AbilityComponent : public Component{
public:

	AbilityComponent(std::string abilityName, int abilityId){
		addAbility(abilityName, abilityId);
	}

	void addAbility(std::string abilityName, int abilityId){
		// bring information form jsonfile with abilityId
		Ability ability;
		ability.abilityId = abilityId;
		ability.abilityName = abilityName;
		ability.abilityLevel = 1;
		ability.abilityNumber = next++;
		
		abilities.push_back(ability);
	}

	std::string getAbilityNameByNum(int num){
		for(auto& ability: abilities){
			if(ability.abilityNumber == num) return ability.abilityName;
		}
		return "none";
	}

	


private:
	int next = 1;
	std::vector<Ability> abilities;

};