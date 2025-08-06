#pragma once
#include <cstddef>
#include <vector>
#include "Types.h"

class ComponentManager;
class EntityManager;



class System {
protected:
  ComponentManager* compMgr;
  EntityManager*   entityMgr;
  const std::vector<ecs::EntityID>& entities;

public:
    System(ComponentManager* cm,
         EntityManager* em,
         const std::vector<ecs::EntityID>& ents)
    : compMgr(cm)
    , entityMgr(em)
    , entities(ents)
    {}

    virtual ~System() = default;
    virtual void update(float deltaTime) = 0;
};

// 컴포넌트 타입 ID를 위한 유틸리티
using SystemTypeID = std::size_t;

inline SystemTypeID getNewSystemTypeID() {
    static SystemTypeID lastID = 0u;
    return lastID++;
}

template<typename S>
inline SystemTypeID getSystemTypeID() noexcept {
    static_assert(std::is_base_of<System, S>::value, "S must inherit from Component");
    static SystemTypeID typeID = getNewSystemTypeID();
    return typeID;
}

constexpr std::size_t MAX_SYSTEMS = 64;

