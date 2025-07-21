#pragma once
#include "ecs/System.h"
#include "ecs/Entity.h"
#include <random>

struct AIModule;

class AISystem : public System{

public:
	void update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime) override;
	void trackTargetsForMissiles(std::shared_ptr<Entity>& entity, AIModule& module);
	void roam(std::shared_ptr<Entity>& entity, AIModule& module);
	bool findOpponent(std::vector<std::shared_ptr<Entity>>&entities, std::shared_ptr<Entity>& missile, AIModule& module);
	void autoAttackTarget(std::shared_ptr<Entity>& entity, AIModule& module, float deltaTime);
	void useAbility(std::shared_ptr<Entity>& entity, AIModule& module, float deltaTime);
	int getRandomNumber(int min, int max) {
	    static std::random_device rd;  // 하드웨어 기반 랜덤 시드
	    static std::mt19937 gen(rd()); // Mersenne Twister 엔진 (매번 다른 난수 생성)
	    std::uniform_int_distribution<> dist(min, max); // 균등 분포

	    return dist(gen);
	}
};	