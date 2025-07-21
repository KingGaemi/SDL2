#pragma once
#include "Component.h"
#include "engine/ecs/core/Types.h"
#include <unordered_map>
#include <vector>

using namespace ecs;

class ComponentManager {
public:

    template<typename T, typename... Args>
    void addComponent(EntityID eid, Args&&... args) {
        ComponentTypeID typeID = getComponentTypeID<T>();
        auto& pool = entityComponents[eid];
        if (componentBitSet[typeID]) {
            // throw std::runtime_error("Component already exists on this entity!");
            std::cout << "Component already exists on this entity!" << std::endl;
            return;
        }else{
            // std::cout << "add Component complete" << std::endl;
        }
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        componentArray[typeID] = component;
        componentBitSet[typeID] = true;
    }

    template<typename T>
    std::shared_ptr<T> getComponent(EntityID eid) const {
        ComponentTypeID typeID = getComponentTypeID<T>();
        if (!componentBitSet[typeID]) return nullptr;
        auto& component = componentArray[typeID];
        return std::static_pointer_cast<T>(component);
    }

    template<typename T>
    bool hasComponent(EntityID eid) const {
        ComponentTypeID typeID = getComponentTypeID<T>();
        return componentBitSet[typeID];
    }

    template<typename T>
    void removeComponent(EntityID eid) {
        ComponentTypeID typeID = getComponentTypeID<T>();
        if (componentBitSet[typeID]) {
            componentBitSet[typeID] = false;
            componentArray[typeID] = nullptr;
            // std::cout << "Remove component complete" << std::endl;
        }else{
            std::cout << "There is no Component like that! " << std::endl;
        }
    }

private:
    struct CompStorage {
        ComponentArray array;
        ComponentBitSet bitset;
    };

    std::unordered_map<EntityID, CompStorage> entityComponents;
    std::unordered_map<ComponentTypeID, std::vector<EntityID>> entityLists;
};