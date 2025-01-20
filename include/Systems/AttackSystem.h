#pragma once

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "Requests.h"

struct AttackEvent {
    int attackerId;         // 공격자 엔티티 ID
    int targetId;			// 대상 엔티티 ID
    int attackTypeId;       // Attack type , 1 = slash, 2 = throw ...   
    float damage;           // 공격력
    float triggerTime;      // 이벤트가 실행될 시간 (지연 공격 등에 사용)
};

struct AbilityCastEvent {
    int casterId;
    int abilityId;
    int targetId;
    float castTime;         // 캐스팅 시간
};


class AttackSystem : public System {

public:
	AttackSystem(std::shared_ptr<ECSManager>& ecsManager) : ecsManager(ecsManager) {}
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
	void push();
private:

	std::shared_ptr<ECSManager> ecsManager;
};






