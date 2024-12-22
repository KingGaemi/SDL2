#pragma once
#include "ECS/Component.h"
#include <iostream>



struct CooldownStruct{

	std::string abilityName;
	float cooldownTime;
	float remainingTime;
	bool isOn;

};


class CooldownComponent : public Component{

public:

	CooldownComponent() {}
	CooldownComponent(const std::string& abilityName, float cooldownTime) {
	    addAbility(abilityName, cooldownTime);
	}

	void addAbility(const std::string& abilityName, float cooldownTime) {
	    cooldownAbilities[abilityName] = {abilityName, cooldownTime, 0.0f, true};
    }

	bool isOnCooldown(const std::string& abilityName) const {
        auto it = cooldownAbilities.find(abilityName);
        // if (it != cooldownAbilities.end()) {
        //     return it->second.remainingTime > 0;
        // }else{
        // 	std::cout << "There is no ability named \"" << abilityName << "\"." << std::endl;
        // }
        // return false;

        if (it != cooldownAbilities.end()) return it->second.isOn;
    }
	void resetCooldown(const std::string& abilityName){

		auto it = cooldownAbilities.find(abilityName);
		if(it != cooldownAbilities.end()){
			it->second.remainingTime = it->second.cooldownTime;
			it->second.isOn = false;
		}
	}


    void updateAllCooldowns(float deltaTime) {
        for (auto& [name, ability] : cooldownAbilities) {
            if (ability.remainingTime > 0.0f) {
                ability.remainingTime -= deltaTime;
                if (ability.remainingTime < 0.0f) {
                    ability.remainingTime = 0.0f;
                    ability.isOn = true; // 음수 방지
                }
            }
        }
    }




	std::unordered_map<std::string, CooldownStruct> cooldownAbilities;

};