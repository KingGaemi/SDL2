#pragma once

#include <cstddef>
#include <typeindex>
#include <type_traits>
#include <memory>

class Component {
public:
    virtual ~Component() = default;
};

// 컴포넌트 타입 ID를 위한 유틸리티
using ComponentTypeID = std::size_t;

inline ComponentTypeID getNewComponentTypeID() {
    static ComponentTypeID lastID = 0u;
    return lastID++;
}

template<typename T>
inline ComponentTypeID getComponentTypeID() noexcept {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
    static const ComponentTypeID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t MAX_COMPONENTS = 64;

