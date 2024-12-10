#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <type_traits>

class Entity;

using ComponentID = std::size_t;


class Component{

public:
    Entity* entity = nullptr;

    virtual void init() = 0;
    virtual void update() = 0;


    virtual ~Component(){}



private:



};

class DrawableComponent : public Component {
public:
    virtual void draw() = 0;
};


inline ComponentID getNewComponentTypeID()

{

    static ComponentID lastID = 0u;
    return lastID++;



}


template <typename T>
inline ComponentID getComponentTypeID() noexcept {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

