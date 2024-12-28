#pragma once

#include "Component.h"
#include <array>
#include <bitset>
#include <memory>
#include <stdexcept>
#include <iostream>

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<std::shared_ptr<Component>, MAX_COMPONENTS>;
using EntityID = std::size_t;


class Entity {
public:
    Entity(EntityID id) : id(id) {}

    EntityID getId() const { return id; }

    template<typename T, typename... Args>
    void addComponent(Args&&... args) {
        ComponentTypeID typeID = getComponentTypeID<T>();
        if (componentBitSet[typeID]) {
            throw std::runtime_error("Component already exists on this entity!");
        }
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        componentArray[typeID] = component;
        componentBitSet[typeID] = true;
    }

    template<typename T>
    std::shared_ptr<T> getComponent() const {
        ComponentTypeID typeID = getComponentTypeID<T>();
        if (!componentBitSet[typeID]) return nullptr;
        auto& component = componentArray[typeID];
        return std::static_pointer_cast<T>(component);
    }

    template<typename T>
    bool hasComponent() const {
        ComponentTypeID typeID = getComponentTypeID<T>();
        return componentBitSet[typeID];
    }


    bool isActive = true;
    bool terminate = false;

private:
    EntityID id;
    ComponentArray componentArray{};
    ComponentBitSet componentBitSet;
};
