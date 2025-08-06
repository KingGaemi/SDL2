#include "Systems/AISystem.h"
#include "Components/AIComponent.h"
#include "Components/AbilityComponent.h"
#include "Components/PositionComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/MovementCommandComponent.h"
#include "Components/CommandComponent.h"
#include "Components/StatusComponent.h"
#include "myMath.h"
#include <algorithm>
// #include <cmath>

#include "Groups.h"

void AISystem::update(float deltaTime) 
{
    // 1) 모든 엔티티 순회
    for (auto& entity : entities) {
        if (!entity->isActive) continue;
        if (!entity->hasComponent<AIComponent>()) continue;

        auto aiComp = entity->getComponent<AIComponent>();
        // 2) AIComponent 안의 aiModulesMap을 순회
        for (auto& [behavior, module] : aiComp->aiModulesMap) {
            // 타이머 갱신
            module.timeAccumulator += deltaTime;
            if (module.timeAccumulator < module.updateInterval) {
                // 아직 업데이트할 시간이 아님
                continue;
            }

            // 이번 프레임에 이 모듈을 업데이트해야 한다면
            // updateInterval마다 timeAccumulator를 0으로 or 빼준다.
            module.timeAccumulator -= module.updateInterval;

            // if(module.aiBehavior == AIBehavior::HomingMissile) std::cout << "findOpponent" << std::endl;
            //   std::cout << "Behavior: " << static_cast<int>(behavior) 
            // << ", timeAccumulator=" << module.timeAccumulator
            // << ", updateInterval=" << module.updateInterval
            // << std::endl;
            // behavior별로 다른 로직 실행
            
            switch (behavior) {
            case AIBehavior::HomingMissile:
                {
                    // 예: findOpponent + Track
                    if (findOpponent(entities, entity, module)) {
                        trackTargetsForMissiles(entity, module);
                        // std::cout<<"HomingMissile"<< std::endl;
                    }
                }
                break;

            case AIBehavior::Roaming:
                {
                    // 예: roam 로직
                    auto statusComp = entity->getComponent<StatusComponent>();
                    // 죽은 상태 등은 스킵
                    if (!statusComp || !statusComp->isAlive) {
                        break;
                    }
                    roam(entity, module);
                }
                break;

            case AIBehavior::Aggressive:
                {
                    auto statusComp = entity->getComponent<StatusComponent>();
                    // 죽은 상태 등은 스킵
                    if (!statusComp || !statusComp->isAlive) {
                        break;
                    }
                    if (findOpponent(entities, entity, module)) {
                        autoAttackTarget(entity, module, deltaTime);
                    }
                }
                break;

            default:
                // std::cout<<"None"<< std::endl;
                // None, etc...
                break;
            }
        }
    }
}

// guideByType


void AISystem::trackTargetsForMissiles(std::shared_ptr<Entity>& entity, AIModule& module) {
    // 필요한 컴포넌트 가져오기
    auto posComp = entity->getComponent<PositionComponent>();
    auto transComp = entity->getComponent<TransformComponent>();
    auto moveCommandComp = entity->getComponent<MovementCommandComponent>();

    // 컴포넌트가 유효한지 확인
    if (!posComp || !transComp || !moveCommandComp ) return;
    transComp->radian = std::fmod(transComp->radian + M_PI, 2 * M_PI) - M_PI;

    // 업데이트 간격 확인

    // 타겟 위치와 미사일 위치 계산
    Vector2D missilePos = posComp->getVector();
    Vector2D targetPos = module.targetPos;
    Vector2D dir = targetPos - missilePos;

    // 목표 각도 계산 (라디안; 0 rad = 오른쪽, 표준 좌표계)
    float desiredAngle = std::atan2(dir.y, dir.x);

    // 현재 각도는 TransformComponent의 회전(도 단위)을 라디안으로 변환한 값
    float currentAngle = transComp->radian;

    // 두 각도의 차이 계산
    float angleDelta = desiredAngle - currentAngle;

    // 각도 차이를 -π ~ π 범위로 정규화
    angleDelta = std::remainder(angleDelta, 2.0f * M_PI);

    
    // Temp..
    MovementCommand moveCommand;
    moveCommand.moveCommandType = MovementCommandType::Spin;
    if(angleDelta > M_PI || angleDelta <= 0 || angleDelta <= -M_PI){
        moveCommand.isClockwise = true;
    }else{
        moveCommand.isClockwise = false;
    }
    if(std::abs(angleDelta) <= 0.3f) moveCommand.stopSpin = true; 
    moveCommandComp->push(moveCommand);
    // 전진 명령
    moveCommand.moveCommandType = MovementCommandType::GoForward;
    // if(angleDelta <= 0) moveCommand.stopSpin = true; // 회전 정지
    moveCommandComp->push(moveCommand);    
}


void AISystem::autoAttackTarget(std::shared_ptr<Entity>& attacker, AIModule& module, float deltaTime) {
    // 필요한 컴포넌트 가져오기
    auto moveCommandComp = attacker->getComponent<MovementCommandComponent>();
    auto posComp = attacker->getComponent<PositionComponent>();   
    // 컴포넌트가 유효한지 확인
    module.stuckTimer += deltaTime;
    if(module.stuckTimer >= 1.0f){
        Vector2D disVec = module.lastPos - posComp->getVector();
        float vectorLength = disVec.x * disVec.x + disVec.y * disVec.y;
        if(vectorLength <= 1000.0f){
            module.lastPos = posComp->getVector();
            module.isStuck = false;
        }else{
            module.isStuck = true;
            // std::cout <<"stuck" <<std::endl;
        }
        module.stuckTimer = 0.0f;
    }
    if (!posComp || !moveCommandComp ) return;

    // 업데이트 간격 확인

    // 타겟 위치와 미사일 위치 계산
    Vector2D attackerPos = posComp->getVector();
    Vector2D targetPos = module.targetPos;
    Vector2D distanceVec = targetPos - attackerPos;
    
    float distance = distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y;
    int hDir, vDir;

    if(distanceVec.x > 0) hDir = 1;
    else hDir = -1;
    if(distanceVec.y > 0) vDir = 1;
    else vDir = -1;
    
    if(std::abs(distanceVec.x)-std::abs(distanceVec.y) > 0){       
        vDir = 0;
    }else{
        hDir = 0;
    }

    float range;    
    Direction dir = {hDir, vDir};
    // std::cout << module.range << std::endl;
    if(attacker->hasComponent<StatusComponent>()){
        auto statusComp = attacker->getComponent<StatusComponent>();
        range = statusComp->range;
    }else{
        range = module.range;
    }
    if(distance <= range) { 
        // std::cout<<"attack" << std::endl;
        if(attacker->hasComponent<CommandComponent>() && module.target) {
            auto commandComp = attacker->getComponent<CommandComponent>();
            Command actionCommand;
            actionCommand.commandType = CommandType::BasicAttack;
            actionCommand.direction = dir;
            if(commandComp) commandComp->push(actionCommand);
            MovementCommand moveCommand;
            moveCommand.direction = dir;
            moveCommand.moveCommandType = MovementCommandType::Stop;
            moveCommandComp->push(moveCommand);  
        }
    }else{
        MovementCommand moveCommand;
        moveCommand.direction = dir;
        moveCommand.moveCommandType = MovementCommandType::MoveToDirection;
        moveCommandComp->push(moveCommand);  
    }


    // if(dir.x >= 1) dir.x = 1;
    // if(dir.x <= -1) dir.x = -1;         
    // if(dir.y >= 1) dir.y = 1;
    // if(dir.y <= -1) dir.y = -1;







}


bool AISystem::findOpponent(std::vector<std::shared_ptr<Entity>>&anothers, std::shared_ptr<Entity>& me, AIModule& module){

	std::vector<std::shared_ptr<Entity>> enemies;
	float shortestSquared = 1000000.0f;
	for(auto& another : anothers){
		if(me->hasComponent<TeamTag>() && another->hasComponent<TeamTag>()){
            auto teamA = me->getComponent<TeamTag>();
			auto teamB = another->getComponent<TeamTag>();
            auto statusB = another->getComponent<StatusComponent>();
            if(!statusB || !statusB->isAlive) continue;
			if(teamA->teamCode == TeamCode::Ally && teamB->teamCode == TeamCode::Enemy) enemies.push_back(another);
            else if(teamA->teamCode == TeamCode::Enemy && teamB->teamCode == TeamCode::Ally) enemies.push_back(another);
		}
	}
    // same as detecting distance

	auto myPos = me->getComponent<PositionComponent>();

	for(auto& target: enemies){
		auto targetPos = target->getComponent<PositionComponent>();
        if(!targetPos || !myPos) continue;

		Vector2D v1 = targetPos->getVector();
        Vector2D v2 = myPos->getVector();
		Vector2D diff =  v1 - v2;

		float lengthSquared = diff.x * diff.x + diff.y * diff.y;
		
		if(lengthSquared < shortestSquared){
			shortestSquared = lengthSquared;			
			module.target = target;
			module.targetPos = targetPos->getVector();
		}
	}

	if(module.target) return true;
	
	return false;
}


void AISystem::roam(std::shared_ptr<Entity>& entity, AIModule& module){
	auto moveCommandComp = entity->getComponent<MovementCommandComponent>();

	if(moveCommandComp){
        MovementCommand moveCommand;
        moveCommand.moveCommandType = MovementCommandType::MoveToDirection;  
		moveCommand.direction = { getRandomNumber(-1, 1) , getRandomNumber(-1, 1)};
		moveCommandComp->push(moveCommand);
	}
}


void AISystem::useAbility(std::shared_ptr<Entity>& entity, AIModule& module, float deltaTime){


    auto abilComp =  entity->getComponent<AbilityComponent>();
    auto statusComp = entity->getComponent<StatusComponent>();
    if(!abilComp || statusComp) return;

    



}