#include "Systems/AISystem.h"
#include "Components/AIComponent.h"
#include "Components/PositionComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include <math.h>
#include "Groups.h"

void AISystem::update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime){
	static float timeAccumulator = 0.0f; // 누적 시간

    // 일정 시간(예: 0.5초)마다 업데이트하도록 설정
    const float updateInterval = 0.1f; // 초 단위

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


	

	for(auto& missile:aiEntities){
		if(findTarget(entities, missile)){
			trackTargetsForMissiles(missile);
		}
	}


}

// guideByType


void AISystem::trackTargetsForMissiles(std::shared_ptr<Entity>& entity){

	auto posComp = entity->getComponent<PositionComponent>();
	auto transComp = entity->getComponent<TransformComponent>();
	auto veloComp = entity->getComponent<VelocityComponent>();
	auto aiComp = entity->getComponent<AIComponent>();

	Vector2D targetPos = aiComp->targetPos;

	if(!posComp||!transComp||!veloComp) return;

	Vector2D missilePos = posComp->getVector();
	Vector2D dir = targetPos - missilePos;

	float desiredAngle = atan2(dir.y, dir.x) * (180.0f / 3.14159f);

	float angleDelta = desiredAngle - transComp->rotation;
	float maxTurnDelta = 30.0f;
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


bool AISystem::findTarget(std::vector<std::shared_ptr<Entity>>&entities, std::shared_ptr<Entity>& missile){

	std::vector<std::shared_ptr<Entity>> enemies;

	for(auto& entity : entities){
		if(entity->hasComponent<TeamTag>()){
			auto teamComp = entity->getComponent<TeamTag>();
			if(teamComp->teamCode == TeamCode::Enemy) enemies.push_back(entity);
		}
	}

	float shortest = 1000.0f; // same as detecting distance

	auto aiComp = missile->getComponent<AIComponent>();
	auto missilePos = missile->getComponent<PositionComponent>();
	for(auto& target: enemies){
		auto targetPos = target->getComponent<PositionComponent>();

		Vector2D v1 = targetPos->getVector();
		Vector2D v2 = missilePos->getVector();

		Vector2D distance =  v1 - v2;
		float length = std::sqrt(distance.x * distance.x + distance.y * distance.y);
		if(length < shortest){
			shortest = length;			
			aiComp->target = target;
			aiComp->targetPos = targetPos->getVector();
		}
	}

	if(aiComp->target) return true;
	
	return false;
}