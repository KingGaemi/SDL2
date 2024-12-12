#pragma once

#include <vector>
#include <memory>

// 전방 선언(Include 최소화)
class Entity;

class System {
public:
    virtual ~System() = default;
    virtual void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) = 0;
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

