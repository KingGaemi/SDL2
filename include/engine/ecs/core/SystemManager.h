#pragma once
#include <memory>
#include <algorithm>
#include <unordered_map>
#include "engine/ecs/core/System.h"


enum class SystemGroup {
    Logic,
    Render,
    UI,
    Event
};

struct SystemRegistration {
    SystemTypeID    typeID;
    std::shared_ptr<System> system;
    SystemGroup group;
    int priority; // 그룹 내 우선순위
};



class SystemManager {

public:
    template<typename S, typename... Args>
    void addSystem(SystemGroup grp, int prio ,Args&&... args) {
        // SystemTypeID typeID = getSystemTypeID<S>();
        // if (systemBitset[typeID]) {
        //     throw std::runtime_error("System already exists on this ECSManager!");
        // }
        auto typeID = getSystemTypeID<S>();
        if (registrationMap.count(typeID)) throw;  // 중복 방지 avoid duplication 
        auto sys = std::make_shared<S>(std::forward<Args>(args)...);
        SystemRegistration reg{typeID, sys, grp, prio };
        auto& vec = systemsByGroup[size_t(grp)];
        vec.push_back(reg);
        std::sort(vec.begin(), vec.end(),
              [](auto&a, auto&b){ return a.priority < b.priority; });
        registrationMap[typeID] = &vec.back();
        // systemArray[typeID] = system;
        // systemBitset[typeID] = true;
    }
    void update(float deltaTime);
    void updateLogic(float deltaTime);

    template<typename S>
    std::shared_ptr<S> getSystem(){
        auto it = registrationMap.find(getSystemTypeID<S>());
        return it != registrationMap.end()
            ? std::dynamic_pointer_cast<S>(it->second->system)
            : nullptr;
    }

    template<typename S>
    void removeSystem() {
        SystemTypeID typeID = getSystemTypeID<S>();

            // 1) registrationMap 에서 제거
            auto it = registrationMap.find(typeID);
            if (it != registrationMap.end()) {
                // 2) 그룹 벡터에서도 제거
                auto grp = it->second->group;
                auto& vec = systemsByGroup[size_t(grp)];
                vec.erase(std::remove_if(vec.begin(), vec.end(),
                    [typeID](auto& reg){ return reg.typeID == typeID; }),
                    vec.end()
                );
                // 3) map 에서도 제거
                registrationMap.erase(it);
            }
    }

private:
    std::unordered_map<SystemTypeID, SystemRegistration*> registrationMap;
    std::array<std::vector<SystemRegistration>, /*num groups*/4> systemsByGroup;
    
};