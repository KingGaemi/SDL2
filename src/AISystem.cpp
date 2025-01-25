#include "Systems/AISystem.h"
#include "Components/AIComponent.h"
#include "Components/PositionComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include <math.h>

void AISystem::update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime){
	static float timeAccumulator = 0.0f; // 누적 시간

    // 일정 시간(예: 0.5초)마다 업데이트하도록 설정
    const float updateInterval = 0.2f; // 초 단위

    // 누적 시간 업데이트
    timeAccumulator += deltaTime;

    // 업데이트 주기가 되지 않으면 바로 반환
    if (timeAccumulator < updateInterval) {
        return;
    }

    // 업데이트 실행 후 타이머 초기화
    timeAccumulator -= updateInterval;


	std::vector<std::shared_ptr<Entity>> aiEntities;

	for(auto& entity: entities){
		if(entity->hasComponent<AIComponent>()){
			if (!entity->isActive) continue;
			aiEntities.push_back(entity);
		}
	}

	for(auto& entity:aiEntities){
		trackTargetsForMissiles(entity);
	}


}

// guideByType


void AISystem::trackTargetsForMissiles(std::shared_ptr<Entity>& entity){

	Vector2D targetPos = {700, 400};

	auto posComp = entity->getComponent<PositionComponent>();
	auto transComp = entity->getComponent<TransformComponent>();
	auto veloComp = entity->getComponent<VelocityComponent>();

	if(!posComp||!transComp||!veloComp) return;

	Vector2D missilePos = posComp->getVector();
	Vector2D dir = targetPos - missilePos;

	float desiredAngle = atan2(dir.y, dir.x) * (180.0f / 3.14159f);

	float angleDelta = desiredAngle - transComp->rotation;
	float maxTurnDelta = 50.0f;
	while (angleDelta > 180.0f)  angleDelta -= 360.0f;
	while (angleDelta < -180.0f) angleDelta += 360.0f;


	if (angleDelta > maxTurnDelta) angleDelta = maxTurnDelta;
	if (angleDelta < -maxTurnDelta) angleDelta = -maxTurnDelta;

	transComp->rotation += angleDelta;

	if (transComp->rotation < 0.0f)        transComp->rotation += 360.0f;
	else if (transComp->rotation >= 360.0f) transComp->rotation -= 360.0f;

	float radians = transComp->rotation * (3.14159f / 180.0f);

	double cosTheta = std::cos(radians);
    double sinTheta = std::sin(radians);

    Vector2D velo = veloComp->velo();
    float speed = veloComp->length(); // veloComp의 속도 크기 (sqrt(vx^2 + vy^2))

	// 보고 있는 방향에 따라 Velocity 설정
	velo.x = speed * cosTheta; // 새로운 x 속도
	velo.y = speed * sinTheta; // 새로운 y 속도

    veloComp->set(velo);
}