#pragma once
#include <cstddef>
#include <bitset>
#include <array>
#include <memory>


namespace ecs { class Component; }

namespace ecs {
    constexpr std::size_t MAX_COMPONENTS = 64;

    using EntityID        = std::size_t;
    using ComponentTypeID = std::size_t;
    using SystemTypeID = std::size_t;
    using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
    using ComponentArray = std::array<std::shared_ptr<Component>, MAX_COMPONENTS>;
}