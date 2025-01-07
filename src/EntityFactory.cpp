#include <iostream>
#include "ECS/EntityFactory.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "Groups.h"

void EntityFactory::createEntity(const SpawnRequest& req) {

	json j;

	if(req.entityType == EntityType::Unit) j = unitsJson;
	else if(req.entityType == EntityType::Projectile) j = projectilesJson;
	else if(req.entityType == EntityType::UI) j = uiJson;
	else if(req.entityType == EntityType::Object) j = objectsJson;
	else{
		std::cerr << "EntityType is \'default\'. Can't create " << std::endl;
		return;
	}
    // 1) JSON 안에 req.name이 존재하는지 확인
    if (!j.contains(req.name)) {
        std::cerr << "No data for " << req.name << " in units.json" << std::endl;
        return;
    }

    // 2) 엔티티 생성
    auto entity = ecsManager->createEntity();

    // 3) components 배열 반복
    auto componentsArray = j[req.name]["components"];
    for (auto& compData : componentsArray) {
        std::string compName = compData.value("name", "UnknownComponent");

        auto it = componentLoaders.find(compName);
        if (it != componentLoaders.end()) {
            // 로더 실행
            it->second(compData, entity);
        } else {
            std::cerr << "No loader for component " << compName << std::endl;
        }
    }

    applyRequests(entity, req);
}

void EntityFactory::applyRequests(std::shared_ptr<Entity> entity, const SpawnRequest& req) {

	if(req.teamCode != TeamCode::Neutral){
		auto teamTag = entity->getComponent<TeamTag>();
		if(teamTag){
			teamTag->teamCode = req.teamCode;
		}
	}
    if(req.hasPosition){
	    auto posComp = entity->getComponent<PositionComponent>();
	    if (posComp) {
            posComp->x = req.x;
            posComp->y = req.y;
	    } 
    }
    if(req.hasDirection){
	    auto directComp = entity->getComponent<DirectionComponent>();
	    if (directComp) {

            directComp->direction.hDir = req.hDir;
            directComp->direction.vDir = req.vDir;
	    }
    }
    if(req.hasTransform){
	    auto transComp = entity->getComponent<TransformComponent>();
	    if (transComp) {
            transComp->width = req.w;
            transComp->height = req.h;
            transComp->scale = req.sc;
	    }
    }
    if(req.hasOwner){
	    auto ownerComp = entity->getComponent<OwnerComponent>();
	    if (ownerComp) {
            ownerComp->ownerId = req.ownerId;
	    }
    }
    if(req.hasDamage){
	    auto damageComp = entity->getComponent<DamageComponent>();
	    if (damageComp) {
	    	damageComp->damage = req.damage;
	    }
    }
}

void EntityFactory::loadPositionComponent(const json& componentData, std::shared_ptr<Entity> entity) {
    
    float x = componentData.value("x", 0.0f);
    float y = componentData.value("y", 0.0f);

    entity->addComponent<PositionComponent>(x, y);
}

void EntityFactory::loadPhysicsComponent(const json& componentData, std::shared_ptr<Entity> entity) {
    
    std::string typeStr = componentData.value("bodyType", "Dynamic");
    BodyType bodyType = BodyType::Dynamic;
    if (typeStr == "Kinematic") bodyType = BodyType::Kinematic;
    else if (typeStr == "Static") bodyType = BodyType::Static;

    entity->addComponent<PhysicsComponent>(bodyType);
}

void EntityFactory::loadSpriteComponent(const json& componentData, std::shared_ptr<Entity> entity) {
   
    std::string texID = componentData.value("textureID", "unknown");
    int w = componentData.value("width", 64);
    int h = componentData.value("height", 64);
    float scale = componentData.value("scale", 1.0f);

    entity->addComponent<SpriteComponent>(texID, w, h, scale);
}

void EntityFactory::loadAnimationComponent(const json& componentData, std::shared_ptr<Entity> entity) {

	std::string typeStr = componentData.value("entityType", "Unit");
	std::string spriteName = componentData.value("spriteName", "unknown");
	std::string filename = "assets/animations/";
	if(typeStr == "Object") filename += "objectAnimations.json";
	else if(typeStr == "UI") filename += "uiAnimations.json";
	else if(typeStr == "Attack") filename += "attackAnimations.json";
	else if(typeStr == "Unit") filename += "unitAnimations.json";

	entity->addComponent<AnimationComponent>(filename, spriteName);
}

void EntityFactory::loadSceneTag(const json& componentData, std::shared_ptr<Entity> entity) {

	std::string typeStr = componentData.value("sceneCode", "Global");
	SceneCode sceneCode;
	if(typeStr == "Game") sceneCode = SceneCode::Game;
	else if(typeStr == "Menu") sceneCode = SceneCode::Menu;
	else if(typeStr == "Global") sceneCode = SceneCode::Global;
	else if(typeStr == "Pause") sceneCode = SceneCode::Pause;
	
	entity->addComponent<SceneTag>(sceneCode);
}

void EntityFactory::loadTeamTag(const json& componentData, std::shared_ptr<Entity> entity) {

	std::string typeStr = componentData.value("teamCode", "Neutral");
	TeamCode teamCode;
	if(typeStr == "Neutral") teamCode = TeamCode::Neutral;
	else if(typeStr == "Ally") teamCode = TeamCode::Ally;
	else if(typeStr == "Enemy") teamCode = TeamCode::Enemy;

	entity->addComponent<TeamTag>(teamCode);
}

void EntityFactory::loadDirectionComponent(const json& componentData, std::shared_ptr<Entity> entity) {

	Direction direction;
	direction.hDir = componentData.value("hDir", 0);
	direction.vDir = componentData.value("vDir", 1);

	entity->addComponent<DirectionComponent>(direction);
}

void EntityFactory::loadVelocityComponent(const json& componentData, std::shared_ptr<Entity> entity) {

	Vector2D velo;
	velo.x = componentData.value("x", 0);
	velo.y = componentData.value("y", 0);

	entity->addComponent<VelocityComponent>(velo);
}

void EntityFactory::loadTransformComponent(const json& componentData, std::shared_ptr<Entity> entity) {

	int w = componentData.value("width", 64);
	int h = componentData.value("height", 64);
	float sc = componentData.value("scale", 1.0f);

	entity->addComponent<TransformComponent>(w, h ,sc);
}

void EntityFactory::loadColliderComponent(const json& componentData, std::shared_ptr<Entity> entity) {

	std::string typeStr = componentData.value("colliderType", "Unit");
	float offsetX = componentData.value("offsetX", 0.0f);
	float offsetY = componentData.value("offsetY", 0.0f);
	ColliderType colliderType;
	if(typeStr == "Unit") colliderType = ColliderType::Unit;
	else if(typeStr == "Projectile") colliderType = ColliderType::Projectile;
	else if(typeStr == "Portal") colliderType = ColliderType::Portal;
	else if(typeStr == "Beacon") colliderType = ColliderType::Beacon;

	int w = componentData.value("width", 64);
	int h = componentData.value("height", 64);
	float sc = componentData.value("scale", 1.0f);

	entity->addComponent<ColliderComponent>(w, h, sc, offsetX, offsetY, colliderType);
}

void EntityFactory::loadStateComponent(const json& componentData, std::shared_ptr<Entity> entity){

	States state;

	std::string typeStr = componentData.value("state", "Idle");
	if(typeStr == "Idle") state = States::Idle;
	else if(typeStr == "Walk") state = States::Walk;
	else if(typeStr == "Run") state = States::Run;
	else if(typeStr == "Death") state = States::Death;
	else if(typeStr == "Hurt") state = States::Hurt;

	entity->addComponent<StateComponent>(state);
}

void EntityFactory::loadStatusComponent(const json& componentData, std::shared_ptr<Entity> entity){

	int maxHp = componentData.value("maxHp", 1);
	int maxMp = componentData.value("maxMp", 1);

	entity->addComponent<StatusComponent>(maxHp, maxMp);
}

void EntityFactory::loadCommandComponent(const json& componentData, std::shared_ptr<Entity> entity){
	entity->addComponent<CommandComponent>();
}

void EntityFactory::loadPlayableComponent(const json& componentData, std::shared_ptr<Entity> entity){
	entity->addComponent<PlayableComponent>();
}

void EntityFactory::loadCooldownComponent(const json& componentData, std::shared_ptr<Entity> entity){

	std::string abilityName = componentData.value("abilityName", "unknown");
	float cooldownTime = componentData.value("cooldownTime", 1.0f);

	entity->addComponent<CooldownComponent>(abilityName, cooldownTime);
}

void EntityFactory::loadDashComponent(const json& componentData, std::shared_ptr<Entity> entity) {
	float dashTimeLimit = componentData.value("dashTimeLimit", 0.17);
	entity->addComponent<DashComponent>(dashTimeLimit);
}

void EntityFactory::loadPlayerTag(const json& componentData, std::shared_ptr<Entity> entity) {
	entity->addComponent<PlayerTag>();
}

void EntityFactory::loadProjectileComponent(const json& componentData, std::shared_ptr<Entity> entity) {
	float speed = componentData.value("speed", 1.0);
	float scale = componentData.value("scale", 1.0);
	float duration = componentData.value("duration", 1.0);

	entity->addComponent<ProjectileComponent>(speed, scale, duration);
}

void EntityFactory::loadDamageComponent(const json& componentData, std::shared_ptr<Entity> entity) {


	int damage = componentData.value("damage", 1);

	entity->addComponent<DamageComponent>(damage);
}








// void UnitEntityFactory::addGeneralComponents(std::shared_ptr<Entity> entity, const SpawnRequest& req){

// 	entity->addComponent<SceneTag>(SceneCode::Game);
// 	entity->addComponent<TeamComponent>(req.teamCode);
// 	entity->addComponent<PositionComponent>(req.x, req.y);
// 	entity->addComponent<DirectionComponent>(0, 1);
// 	entity->addComponent<VelocityComponent>();
// 	entity->addComponent<TransformComponent>(req.w, req.h, req.sc);
// 	entity->addComponent<ColliderComponent>(req.w*req.sc, req.h*req.sc, req.type);

// 	entity->addComponent<StateComponent>();
// 	entity->addComponent<SolidComponent>();

// }



// void EntityFactory::registerComponentLoaders() {
//     componentLoaders["PositionComponent"]     = loadPositionComponent;
//     componentLoaders["PhysicsComponent"]      = loadPhysicsComponent;
//     componentLoaders["SpriteComponent"]       = loadSpriteComponent;
//     componentLoaders["AnimationComponent"]    = loadAnimationComponent;
//     componentLoaders["SceneTag"]              = loadSceneTag;
//     componentLoaders["TeamTag"]               = loadTeamTag;
//     componentLoaders["DirectionComponent"]    = loadDirectionComponent;
//     componentLoaders["VelocityComponent"]     = loadVelocityComponent;
//     componentLoaders["TransformComponent"]    = loadTransformComponent;
//     componentLoaders["ColliderComponent"]     = loadColliderComponent;
//     componentLoaders["StateComponent"]        = loadStateComponent;
//     componentLoaders["StatusComponent"]       = loadStatusComponent;
//     componentLoaders["CommandComponent"]      = loadCommandComponent;
//     componentLoaders["PlayableComponent"]     = loadPlayableComponent;
// }

void EntityFactory::registerComponentLoaders() {
    componentLoaders["PositionComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadPositionComponent(data, entity);
    };
    componentLoaders["PhysicsComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadPhysicsComponent(data, entity);
    };
    componentLoaders["SpriteComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadSpriteComponent(data, entity);
    };
    componentLoaders["AnimationComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadAnimationComponent(data, entity);
    };
    componentLoaders["SceneTag"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadSceneTag(data, entity);
    };
    componentLoaders["TeamTag"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadTeamTag(data, entity);
    };
    componentLoaders["DirectionComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadDirectionComponent(data, entity);
    };
    componentLoaders["VelocityComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadVelocityComponent(data, entity);
    };
    componentLoaders["TransformComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadTransformComponent(data, entity);
    };
    componentLoaders["ColliderComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadColliderComponent(data, entity);
    };
    componentLoaders["StateComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadStateComponent(data, entity);
    };
    componentLoaders["StatusComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadStatusComponent(data, entity);
    };
    componentLoaders["CommandComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadCommandComponent(data, entity);
    };
    componentLoaders["DashComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadPlayableComponent(data, entity);
    };
    componentLoaders["PlayableComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadDashComponent(data, entity);
    };
    componentLoaders["PlayerTag"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadPlayerTag(data, entity);
    };
    componentLoaders["CooldownComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadCooldownComponent(data, entity);
    };
     componentLoaders["ProjectileComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadProjectileComponent(data, entity);
    };
    componentLoaders["DamageComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadDamageComponent(data, entity);
    };
}
