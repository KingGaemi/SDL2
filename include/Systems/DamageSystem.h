#pragma once

#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "Groups.h"
#include <unordered_set>



struct PairHash {
    std::size_t operator()(const std::pair<EntityID, EntityID>& p) const {
        auto h1 = std::hash<EntityID>()(p.first);
        auto h2 = std::hash<EntityID>()(p.second);
        // 간단한 방법: XOR or combine
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

struct PairEqual {
    bool operator()(const std::pair<EntityID, EntityID>& a, 
                    const std::pair<EntityID, EntityID>& b) const {
        return (a.first == b.first) && (a.second == b.second);
    }
};


class DamageSystem : public System{

public:

	DamageSystem(std::shared_ptr<ECSManager> ecsManager) : ecsManager(ecsManager) {}

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
	void applyDamage(std::shared_ptr<Entity> attacker, std::shared_ptr<Entity> target);

private:

	std::shared_ptr<ECSManager> ecsManager;
	std::unordered_set<std::pair<EntityID, EntityID>, PairHash, PairEqual> alreadyAttacked;

};