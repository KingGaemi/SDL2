#pragma once
#include <vector>
#include <memory>

class Entity;

class System {
public:
    virtual ~System() {}

    virtual void update(std::vector<std::shared_ptr<Entity>>& entities) = 0;
    virtual void render(std::vector<std::shared_ptr<Entity>>& entities) = 0;
};
