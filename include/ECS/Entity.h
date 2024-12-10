#pragma once
#include "Component.h"
#include <cstdint>
#include <unordered_set>
#include <vector>
#include <bitset>
#include <array>
#include <memory>
#include <cassert>
#include <optional>
#include <stdexcept>



class ECSManager;




using Group = std::size_t;



constexpr std::size_t MaxComponents = 32;



using ComponentBitSet = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component*, MaxComponents>;


class Entity {
public:
    using ID = std::uint32_t;
    Entity(ECSManager& p_manager, ID p_id) : id(p_id), manager(p_manager),  active(true){}


    void update();
    void destroy(){active = false;}
    bool isActive() const {return active;}


    template <typename T, typename... Args>
    T& addComponent(Args&&... args){
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
        const ComponentID typeID = getComponentTypeID<T>();
        T* comp = new T(std::forward<Args>(args)...);
        comp->entity = this;
        components.emplace_back(comp);
        componentArray[typeID] = comp;
        componentBitset[typeID] = true;

        comp->init();

        return *comp;   


    }


    template <typename T>
    bool hasComponent() const{

        return componentBitset[getComponentTypeID<T>()];

    }


    template <typename T>
    T& getComponent() const{
        const ComponentID typeID = getComponentTypeID<T>();
        assert(componentBitset[typeID] && "Component not found!");
        return *static_cast<T*>(componentArray[typeID]);
    }

    const std::vector<std::unique_ptr<Component>>& getAllComponents() const {
        return components;
    }


    void setName(const std::string& newName) {
        name = newName;
    }

    bool hasName() const {
        return name.has_value(); // 이름이 있는지 확인
    }

    std::string getName() const {
        if (name) {
            return name.value(); // 이름이 있으면 반환
        } else {
            throw std::runtime_error("Entity has no name!");
        }
    }



private:
    ID id;
    ECSManager& manager;
    bool active = false;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray{nullptr};
    ComponentBitSet componentBitset;

    std::optional<std::string> name;

};

