#pragma once
#include <memory>
#include <algorithm>
#include "engine/ecs/core/System.h"


enum class SystemGroup {
    Logic,
    Render,
    UI,
    Event
};

struct SystemRegistration {
    std::shared_ptr<System> system;
    SystemGroup group;
    int priority; // 그룹 내 우선순위
};



class SystemManager {

public:
    template<typename S, typename... Args>
    void addSystem(SystemGroup group, int priority ,Args&&... args) {
        // SystemTypeID typeID = getSystemTypeID<S>();
        // if (systemBitset[typeID]) {
        //     throw std::runtime_error("System already exists on this ECSManager!");
        // }
        auto system = std::make_shared<S>(std::forward<Args>(args)...);
        SystemRegistration reg;
        reg.system   = system;
        reg.group    = group;
        reg.priority = priority;
        registeredSystems.push_back(reg);

        // systemArray[typeID] = system;
        // systemBitset[typeID] = true;
    }
    void update(float deltaTime);
    void updateLogic(float deltaTime);
    void render(float deltaTime);
    void renderUI(float deltaTime);

    template<typename S>
    std::shared_ptr<S> getSystem(){
        for (auto& reg : registeredSystems) {
            auto casted = std::dynamic_pointer_cast<S>(reg.system);
            if (casted) {
                return casted;
            }
        }
        return nullptr;
    }

    template<typename S>
    void removeSystem() {
        registeredSystems.erase(
            std::remove_if(registeredSystems.begin(), registeredSystems.end(),
                [](auto& reg){
                    return (std::dynamic_pointer_cast<S>(reg.system) != nullptr);
                }),
            registeredSystems.end()
        );
    }

private:
    std::vector<SystemRegistration> registered;
    
};