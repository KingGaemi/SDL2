#pragma once
#include <cstdint>
#include <unordered_set>
#include <vector>


class Manager
class Component;


constexpr size_t MaxComponents = 32; // 
using ComponentBitSet = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component*, MaxComponents>;


class Entity {
public:

    Entity(Manager& p_manager) : p_manager(manager){}


    void update();
    void draw();
    void destroy(){active = false}
    bool isActive() const {return active;}


    template <typename T, typename... Args>
    T& addComponent(Args&&... args);

    template <typename T>
    bool hasComponent() const;

    template <typename T>
    T& getComponent() const;



private:
    Manager& manager;
    bool active = false;
    std::vector<std::unique_ptr<Component>> components;

    ComponentBitSet componentBitset;
    ComponentArray componentArray{};

};
