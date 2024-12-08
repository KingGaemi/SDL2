#pragma once


using ComponentID = std::size_t;
constexpr std::size_t MaxComponents = 32;


class Component{

public:
    Entity* entity = nullptr;

    virtual void init();
    virtual void update();
    virtual void draw();

    virtual ~Component(){}



private:



};


inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}