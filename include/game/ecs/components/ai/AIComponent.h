#pragma once
#include "engine/ecs/core/Component.h"

#include "engine/ecs/core/Entity.h"
#include "engine/math/Vector2D.h"
#include <unordered_map>


enum class AIBehavior{
	HomingMissile,
	Roaming,
	FindOpponent,
	Aggressive,
	None
};

struct AIModule {
	AIBehavior aiBehavior = AIBehavior::None;
	std::shared_ptr<Entity> target = nullptr;
	Vector2D targetPos = {0,0};

	float updateInterval = 0.1f;
	float timeAccumulator = 0.0f;
	float stuckTimer = 0.0f;
	Vector2D lastPos;
	float priority;
	float range;
	bool isStuck;
};

class AIComponent : public Component {
public:
	AIComponent(AIBehavior aiBehavior) {
		addModule(aiBehavior);
	}

	AIModule& findModule (AIBehavior targetBehavior) {

		auto it = aiModulesMap.find(targetBehavior);
		if (it != aiModulesMap.end()) {
		    // std::cout << "Found AIModule with behavior: " << static_cast<int>(it->first) << std::endl;
		    return it->second;
		} 
	    std::cout << "Not found! Returning default AIModule." << std::endl;
        return defaultModule; 
			
	}


	void addModule(AIBehavior aiBehavior){
		AIModule module;
		module.aiBehavior = aiBehavior;
		if(aiBehavior == AIBehavior::HomingMissile) module.updateInterval = 0.03f;
		if(aiBehavior == AIBehavior::Roaming) module.updateInterval = 3.0f;
		if(aiBehavior == AIBehavior::Aggressive) module.updateInterval = 0.1f;
		aiModulesMap.insert({aiBehavior, module});
	}



	std::unordered_map<AIBehavior, AIModule> aiModulesMap;
private:
	AIModule defaultModule; // 
};