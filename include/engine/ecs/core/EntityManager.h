#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "engine/ecs/core/Entity.h"


class IEntityManager {
public:
    virtual ~IEntityManager() = default;
    virtual std::shared_ptr<Entity> create() = 0;
    virtual void destroy(const std::shared_ptr<Entity>& e) = 0;
    virtual std::shared_ptr<Entity> getById(std::size_t id) const = 0;
};



class EntityManager : public IEntityManager {
  // 실제 구현
public:
    EntityManager() = default;
    ~EntityManager() override = default;

    std::shared_ptr<Entity> create() override;
    void destroy(const std::shared_ptr<Entity>& e) override;

    std::shared_ptr<Entity> getById(std::size_t id) const override;
    std::vector<std::shared_ptr<Entity>>& getEntities(){return entities;}

private:
    std::size_t nextID = 0;
    // function
    // std::shared_ptr<Entity> createEntity();
    // void destroyEntity(std::shared_ptr<Entity> e);
    // std::shared_ptr<Entity> getEntityById(std::size_t id);
    // std::shared_ptr<Entity> getEntityByName(const std::string& name);



    std::vector<std::shared_ptr<Entity>> entities;

};  
