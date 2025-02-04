#include "Systems/AISystem.h"
#include "Components/AIComponent.h"
#include "Components/PositionComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/MovementCommandComponent.h"
#include "Components/StatusComponent.h"
#include "myMath.h"
#include <algorithm>
// #include <cmath>

#include "Groups.h"

void AISystem::update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime){

	std::vector<std::shared_ptr<Entity>> homingAI;
	std::vector<std::shared_ptr<Entity>> roamingAI;
	std::vector<std::shared_ptr<Entity>> targetingAI;

	for(auto& entity: entities){
		if(entity->hasComponent<AIComponent>()){
			if (!entity->isActive) continue;
			auto aiComp = entity->getComponent<AIComponent>();
			if(aiComp->aiType == AIType::HomingMissile){
				homingAI.push_back(entity);
				aiComp->updateInterval = 0.05f;
			}else if(aiComp->aiType == AIType::Roaming){
				auto statusComp = entity->getComponent<StatusComponent>();
				if(!statusComp || !statusComp->isAlive) continue;
				roamingAI.push_back(entity);
				aiComp->updateInterval = 1.0f;
			}
		}
	}

	for(auto& missile: homingAI){
	
		if(findTarget(entities, missile)){
			trackTargetsForMissiles(missile, deltaTime);
		}
	}

	for(auto& roamer: roamingAI){
		roam(roamer, deltaTime);
	}


}

// guideByType


void AISystem::trackTargetsForMissiles(std::shared_ptr<Entity>& entity, float deltaTime) {
    // 필요한 컴포넌트 가져오기
    auto posComp = entity->getComponent<PositionComponent>();
    auto transComp = entity->getComponent<TransformComponent>();
    auto aiComp = entity->getComponent<AIComponent>();
    transComp->radian = std::fmod(transComp->radian + M_PI, 2 * M_PI) - M_PI;
    // 컴포넌트가 유효한지 확인
    if (!posComp || !transComp || !aiComp) return;

    // 업데이트 간격 확인
    aiComp->timeAccumulator += deltaTime;
    if (aiComp->timeAccumulator < aiComp->updateInterval) return;

    // 타겟 위치와 미사일 위치 계산
    Vector2D missilePos = posComp->getVector();
    Vector2D targetPos = aiComp->targetPos;
    Vector2D dir = targetPos - missilePos;

    // 목표 각도 계산 (라디안; 0 rad = 오른쪽, 표준 좌표계)
    float desiredAngle = std::atan2(dir.y, dir.x);

    // 현재 각도는 TransformComponent의 회전(도 단위)을 라디안으로 변환한 값
    float currentAngle = transComp->radian;

    // 두 각도의 차이 계산
    float angleDelta = desiredAngle - currentAngle;

    // 각도 차이를 -π ~ π 범위로 정규화
    angleDelta = std::fmod(angleDelta + M_PI, 2 * M_PI) - M_PI;

    // 최대 회전 각도 제한 (예: 30도)
    float maxTurnDelta = 15.0f * (M_PI / 180.0f);
    angleDelta = std::clamp(angleDelta, -maxTurnDelta, maxTurnDelta);

    // 새 각도 계산
    currentAngle += angleDelta;

    // TransformComponent에 새 각도 (라디안 → 도)로 저장
    // transComp->rotation = toAngle(currentAngle);
    transComp->radian += angleDelta;

    // (필요에 따라 새로운 속도 벡터 계산 및 속도 업데이트하는 부분이 있다면 추가)

    // 시간 누적기 초기화
    aiComp->timeAccumulator -= aiComp->updateInterval;
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
		if(!aiComp->target) shortest = 1000.0f;
		if(length < shortest){
			shortest = length;			
			aiComp->target = target;
			aiComp->targetPos = targetPos->getVector();
		}
	}

	if(aiComp->target) return true;
	
	return false;
}


void AISystem::roam(std::shared_ptr<Entity>& entity, float deltaTime){

	auto directComp = entity->getComponent<PositionComponent>();
	auto aiComp = entity->getComponent<AIComponent>();

	aiComp->timeAccumulator += deltaTime;
	if(aiComp->timeAccumulator < aiComp->updateInterval) return;

	auto moveCommandComp = entity->getComponent<MovementCommandComponent>();

	if(moveCommandComp){
		moveCommandComp->direction = { getRandomNumber(-1, 1) , getRandomNumber(-1, 1)};
		moveCommandComp->moveCommandType = MovementCommandType::Move;
	}

	aiComp->timeAccumulator -= aiComp->updateInterval;

}