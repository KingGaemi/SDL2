#pragma once
#include "Entity.h"
#include "Component.h"

#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>
#include <optional>


class ECSManager{

public:
	using EntityList = std::vector<std::shared_ptr<Entity>>;

    std::shared_ptr<Entity> createEntity();
    std::shared_ptr<Entity> getEntityByName(const std::string& name);
    void setEntityName(std::shared_ptr<Entity> entity, const std::string& name);
    std::optional<std::string> getEntityName(std::shared_ptr<Entity> entity) const;

    void update();
    void draw();


private:

    EntityList entities;
    std::size_t nextID = 0;
    std::unordered_map<std::shared_ptr<Entity>, std::string> entityNames;
    std::unordered_map<std::string, std::shared_ptr<Entity>> entityByName;
};


