    #pragma once

#include "Component.h"
#include <array>
#include <bitset>
#include <memory>
#include <stdexcept>
#include <iostream>

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<std::shared_ptr<Component>, MAX_COMPONENTS>;

class Entity {
public:
    Entity(std::size_t id) : id(id) {}

    std::size_t getId() const { return id; }

    template<typename T, typename... Args>
    void addComponent(Args&&... args) {
        ComponentTypeID typeID = getComponentTypeID<T>();
        if (componentBitset[typeID]) {
            throw std::runtime_error("Component already exists on this entity!");
        }
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        componentArray[typeID] = component;
        componentBitset[typeID] = true;


        std::cout << "addComponent : " << typeID << std::endl;
    }

    template<typename T>
    std::shared_ptr<T> getComponent() const {
        ComponentTypeID typeID = getComponentTypeID<T>();
        if (!componentBitset[typeID]) return nullptr;
        auto& component = componentArray[typeID];

        std::cout << "getComponent : " << typeID << std::endl;
        return std::static_pointer_cast<T>(component);
    }

    template<typename T>
    bool hasComponent() const {
        ComponentTypeID typeID = getComponentTypeID<T>();
        return componentBitset[typeID];
    }

    bool isActive = true;

private:
    std::size_t id;
    ComponentArray componentArray{};
    ComponentBitset componentBitset;
};
