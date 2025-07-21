#pragma once

#include "ecs/Entity.h"
#include "ecs/System.h"
#include "ecs/ECSManager.h"
#include "Events/EventManager.h"
#include "Manager/SoundManager.h"
#include "Requests.h"

// struct AttackEvent {
//     int attackerId;         // 공격자 엔티티 ID
//     int targetId;			// 대상 엔티티 ID
//     int attackTypeId;       // Attack type , 1 = slash, 2 = throw ...   
//     float damage;           // 공격력
//     float triggerTime;      // 이벤트가 실행될 시간 (지연 공격 등에 사용)
// };

// struct AbilityCastEvent {
//     int casterId;
//     int abilityId;
//     int targetId;
//     float castTime;         // 캐스팅 시간
// };


class AttackSystem : public System {

public:
	AttackSystem(std::shared_ptr<ECSManager>& ecsManager, std::shared_ptr<EventManager>& eventManager, std::shared_ptr<SoundManager>& soundManager) : ecsManager(ecsManager), eventManager(eventManager), soundManager(soundManager) {}
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
    void teskEvent(const AttackEvent& event);
    void castSpell(const AttackEvent& event);
    void basicAttack(const AttackEvent& event);
    void shootArrow(const AttackEvent& event);
    void whirlBlade(const AttackEvent& event);
    void releaseBomb(const AttackEvent& event);
    float getAngleFromDirection(int hDir, int vDir);
	
private:

	std::shared_ptr<ECSManager> ecsManager;
    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<SoundManager> soundManager;
};






