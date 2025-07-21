#pragma once 
#include "ecs/System.h"
#include "ecs/Entity.h"
#include "ecs/ECSManager.h"
#include "Requests.h"
#include <random>


class SpawnSystem : public System {

public:
	SpawnSystem(std::shared_ptr<ECSManager>& ecsManager) : ecsManager(ecsManager){}
	void update(std::vector<std::shared_ptr<Entity>>&entities , float deltaTime) override;


	int getRandomNumber(int min, int max) {
	    static std::random_device rd;  // 하드웨어 기반 랜덤 시드
	    static std::mt19937 gen(rd()); // Mersenne Twister 엔진 (매번 다른 난수 생성)
	    std::uniform_int_distribution<> dist(min, max); // 균등 분포

	    return dist(gen);
	}

private:
	std::shared_ptr<ECSManager> ecsManager;
};