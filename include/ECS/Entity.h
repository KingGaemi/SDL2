#pragma once
#include <cstdint>
#include <unordered_set>

class Entity {
public:
    using ID = std::uint32_t;

    explicit Entity(ID id) : id(id) {}
    ID getId() const { return id; }

private:
    ID id;
};
