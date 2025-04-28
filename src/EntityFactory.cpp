#include <iostream>
#include "ECS/EntityFactory.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "Groups.h"

void EntityFactory::configureEntity(const SpawnRequest& req, std::shared_ptr<Entity>& entity) {

	json j;

	if(req.entityType == EntityType::Unit) j = unitsJson;
	else if(req.entityType == EntityType::Projectile) j = projectilesJson;
	else if(req.entityType == EntityType::UI) j = uiJson;
	else if(req.entityType == EntityType::Object) j = objectsJson;
	else if(req.entityType == EntityType::Item) j = itemsJson;
    else if(req.entityType == EntityType::Image) j = imagesJson;
	else if(req.entityType == EntityType::Props){
		makeProps(req);
		return;
	}else if(req.entityType == EntityType::Camera){
		return;
    }else if(req.entityType == EntityType::Text){
		std::cerr << "EntityType is \'default\'. Can't create " << std::endl;
		return;
	}else{
		std::cerr << "EntityType is \'default\'. Can't create " << std::endl;
		return;
	}
    // 1) JSON 안에 req.name이 존재하는지 확인
    if (!j.contains(req.name)) {
        std::cerr << "No data for \'" << req.name << "\' in units.json" << std::endl;
        return;
    }

    
    if(req.entityType == EntityType::UI) entity->addComponent<UITag>();
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

    if(!entity->hasComponent<SceneTag>()){
    	entity->addComponent<SceneTag>(gameManager->getCurrentScene());
    	std::cout << "entity " << entity->getId() << " didn't have SceneTag" << std::endl;
    } 
}

void EntityFactory::makeProps(const SpawnRequest& req){
	auto prop = ecsManager->createEntity();
	prop->addComponent<PositionComponent>((req.x + req.w/2) * 2, (req.y + req.h/2) * 2);
    prop->addComponent<TransformComponent>(req.w, req.h, req.sc);
    prop->addComponent<PhysicsComponent>(req.w, req.h, req.sc, BodyType::Static);
    prop->addComponent<SceneTag>(SceneCode::Game);
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
    if(req.hasVelocity){
	    auto veloComp = entity->getComponent<VelocityComponent>();
	    auto projectileComp = entity->getComponent<ProjectileComponent>();
	    if (veloComp && projectileComp) {
            veloComp->set(req.hDir * req.projectileSpeed * projectileComp->projectileSpeed,
            			  req.vDir * req.projectileSpeed * projectileComp->projectileSpeed);
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
            if(req.w != 0)transComp->width = req.w;
            if(req.h != 0)transComp->height = req.h;
            transComp->scale = req.sc;
            transComp->radian = toRadian(req.rotation);
	    }
    }
    if(req.hasOwner){
	    auto projectileComp = entity->getComponent<ProjectileComponent>();
	    if (projectileComp) {
            projectileComp->ownerId = req.ownerId;
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

    float offsetX = componentData.value("offsetX", 0.0f);
	float offsetY = componentData.value("offsetY", 0.0f);
	float rotation = componentData.value("rotation", 0.0f);;
	int w = componentData.value("width", 64);
	int h = componentData.value("height", 64);
	float sc = componentData.value("scale", 1.0f);
	bool fixedRotation = componentData.value("fixedRotation", false);

    BodyType bodyType = BodyType::Dynamic;
    if (typeStr == "Kinematic") bodyType = BodyType::Kinematic;
    else if (typeStr == "Static") bodyType = BodyType::Static;

    entity->addComponent<PhysicsComponent>(w, h, sc, offsetX, offsetY, rotation, bodyType, fixedRotation);
}

void EntityFactory::loadSpriteComponent(const json& componentData, std::shared_ptr<Entity> entity) {
   
    std::string texId = componentData.value("textureID", "unknown");
    float w = componentData.value("width", 64);
    float h = componentData.value("height", 64);
    float scale = componentData.value("scale", 1.0f);
    bool hasDirectional = componentData.value("hasDirectional", false);

    entity->addComponent<SpriteComponent>(texId, w, h, scale, hasDirectional);
}

void EntityFactory::loadAnimationComponent(const json& componentData, std::shared_ptr<Entity> entity) {

	std::string typeStr = componentData.value("entityType", "Unit");
	std::string category  = componentData.value("category", "none");
	std::string spriteName = componentData.value("spriteName", "unknown");
	std::string filename = "res/gfx/sprite_sheets/";
	if(typeStr == "Object") filename += "object/";
	else if(typeStr == "UI") filename += "ui/";
	else if(typeStr == "Attack") filename += "attack/";
	else if(typeStr == "Unit") filename += "unit/";
	else if(typeStr == "Item") filename += "item/";
	else if(typeStr == "Projectile") filename += "projectile/";

	filename += category + "/" + spriteName + ".json";


	entity->addComponent<AnimationComponent>(filename);
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

void EntityFactory::loadHpBarComponent(const json& componentData, std::shared_ptr<Entity> entity) {

	int type = componentData.value("type", 1);
	float offsetX = componentData.value("offsetX", 0);
	float offsetY = componentData.value("offsetY", 0);
	int w = componentData.value("w", 34);
	int h = componentData.value("h", 5);
	float scale = componentData.value("scale", 2.0f);
	
	entity->addComponent<HpBarComponent>(w, h, type, offsetY, scale);
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
	float radius = componentData.value("radius", 0.0f);
	ColliderType colliderType;
	if(typeStr == "Unit") colliderType = ColliderType::Unit;
	else if(typeStr == "Projectile") colliderType = ColliderType::Projectile;
	else if(typeStr == "Portal") colliderType = ColliderType::Portal;
	else if(typeStr == "Beacon") colliderType = ColliderType::Beacon;

	int w = componentData.value("width", 64);
	int h = componentData.value("height", 64);
	float sc = componentData.value("scale", 1.0f);

	if(radius == 0.0f){
		entity->addComponent<ColliderComponent>(w, h, sc, offsetX, offsetY, colliderType);
	}else{
		entity->addComponent<ColliderComponent>(radius, offsetX, offsetY, colliderType);
	}
}

void EntityFactory::loadStateComponent(const json& componentData, std::shared_ptr<Entity> entity){

	entity->addComponent<StateComponent>();
}

void EntityFactory::loadStatusComponent(const json& componentData, std::shared_ptr<Entity> entity){

	int maxHp = componentData.value("maxHp", 1);
	int maxMp = componentData.value("maxMp", 1);
	float movementSpeed = componentData.value("movementSpeed", 100.0f);
	float attackSpeed = componentData.value("attackSpeed", 1.0f);
    int physicalDamage = componentData.value("physicalDamage", 10);

	entity->addComponent<StatusComponent>(maxHp, maxMp, attackSpeed, movementSpeed, physicalDamage);
}

void EntityFactory::loadCommandComponent(const json& componentData, std::shared_ptr<Entity> entity){
	entity->addComponent<CommandComponent>();
}

void EntityFactory::loadMovementCommandComponent(const json& componentData, std::shared_ptr<Entity> entity){

	std::string typeStr = componentData.value("commandType", "Stop");
	MovementCommandType type;

	if(typeStr == "Hold") type = MovementCommandType::Hold;
	else if(typeStr == "MoveToDirection") type = MovementCommandType::MoveToDirection;
	else if(typeStr == "GoForward") type = MovementCommandType::GoForward;
	else if(typeStr == "Spin") type = MovementCommandType::Spin;

	entity->addComponent<MovementCommandComponent>(type);
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
void EntityFactory::loadUITag(const json& componentData, std::shared_ptr<Entity> entity) {
	entity->addComponent<UITag>();
}
void EntityFactory::loadTextTag(const json& componentData, std::shared_ptr<Entity> entity) {
	entity->addComponent<TextTag>();
}
void EntityFactory::loadIMGTag(const json& componentData, std::shared_ptr<Entity> entity) {
	entity->addComponent<IMGTag>();
}
void EntityFactory::loadCoreTag(const json& componentData, std::shared_ptr<Entity> entity) {
	entity->addComponent<CoreTag>();
}
void EntityFactory::loadBossTag(const json& componentData, std::shared_ptr<Entity> entity) {
	entity->addComponent<BossTag>();
}



void EntityFactory::loadProjectileComponent(const json& componentData, std::shared_ptr<Entity> entity) {
	float speed = componentData.value("speed", 1.0);
	float scale = componentData.value("scale", 1.0);
	float duration = componentData.value("duration", 1.0);
	int penetration = componentData.value("penetration", 0);
	std::string attackType = componentData.value("attackType", "none");
	entity->addComponent<ProjectileComponent>(speed, scale, duration, penetration, attackType);
}

void EntityFactory::loadDamageComponent(const json& componentData, std::shared_ptr<Entity> entity) {


	int damage = componentData.value("damage", 1);
	std::string attackType = componentData.value("attackType", "none");

	entity->addComponent<DamageComponent>(damage, attackType);
}

void EntityFactory::loadItemComponent(const json& componentData, std::shared_ptr<Entity> entity) {

	int itemId = componentData.value("itemId", 1);
	bool stackable = componentData.value("stackable", false);
	int maxStackCounts = componentData.value("maxStackCounts", 1);

	entity->addComponent<ItemComponent>(itemId, stackable, maxStackCounts);
}
void EntityFactory::loadFloatingEffectComponent(const json& componentData, std::shared_ptr<Entity> entity) {
	entity->addComponent<FloatingEffectComponent>();
}

void EntityFactory::loadAbilityComponent(const json& componentData, std::shared_ptr<Entity> entity) {

	std::string abilityName = componentData.value("name", "none");
	int abilityId = componentData.value("id", 1);

	entity->addComponent<AbilityComponent>(abilityName, abilityId); 
}

void EntityFactory::loadAIComponent(const json& componentData, std::shared_ptr<Entity> entity) {
    std::string aiBehaviorType = componentData.value("AIType", "Roaming");
    float range = componentData.value("range", 0.0f);
    AIBehavior aiBehavior;

    if(aiBehaviorType == "HomingMissile"){
    	aiBehavior = AIBehavior::HomingMissile;
    }else if(aiBehaviorType == "Roaming"){
    	aiBehavior = AIBehavior::Roaming;
    }else if(aiBehaviorType == "FindOpponent"){
    	aiBehavior = AIBehavior::FindOpponent;
    }else if(aiBehaviorType == "Aggressive"){
    	aiBehavior = AIBehavior::Aggressive;
    }else {
    	aiBehavior = AIBehavior::None;
    }

    entity->addComponent<AIComponent>(aiBehavior);

    if(range != 0.0f){
    	auto aiComp = entity->getComponent<AIComponent>();
    	auto& module = aiComp->findModule(aiBehavior);
    	module.range = range;
    }

}

void EntityFactory::loadSpawnerComponent(const json& componentData, std::shared_ptr<Entity> entity) {
    
    std::string spawnName = componentData.value("spawnName", "none");
    float spawnTime = componentData.value("spawnTime", 1.0f);
    std::string spawnType = componentData.value("spawnType", "Unit");

    SpawnRequest req;

    if(spawnType == "Item") req.entityType= EntityType::Item;
    else req.entityType = EntityType::Unit;
    req.name = spawnName;
    req.teamCode = TeamCode::Enemy;

    entity->addComponent<SpawnerComponent>(req, spawnTime);
}


void EntityFactory::loadHitboxComponent(const json& componentData, std::shared_ptr<Entity> entity) {
    
    int w = componentData.value("w", 1);
    int h = componentData.value("h", 1);
    float offsetX = componentData.value("offsetX", 0);
    float offsetY = componentData.value("offsetY", 0);
    float scale = componentData.value("scale", 1.0f);

    entity->addComponent<HitboxComponent>(w, h, offsetX, offsetY, scale);
}

void EntityFactory::loadHpBarTag(const json& componentData, std::shared_ptr<Entity> entity){
	entity->addComponent<HpBarTag>();
}

void EntityFactory::loadShadowComponent(const json& componentData, std::shared_ptr<Entity> entity) {
    
    float w = componentData.value("width", 32);
    float h = componentData.value("height", 32);
    float sc = componentData.value("scale", 0.0f);
    float offsetX = componentData.value("offsetX", 0.0f);
	float offsetY = componentData.value("offsetY", 0.0f);

    entity->addComponent<ShadowComponent>(w, h, sc, offsetX, offsetY);
}
void EntityFactory::loadShakeEffectComponent(const json& componentData, std::shared_ptr<Entity> entity) {

    entity->addComponent<ShakeEffectComponent>();
}

void EntityFactory::loadSoundEffectComponent(const json& componentData, std::shared_ptr<Entity> entity) {
    
    std::string bodyMaterial = componentData.value("bodyMaterial", "None");
    std::string footMaterial = componentData.value("footMaterial", "None");
    std::string typeMaterial = componentData.value("typeMaterial", "None");
    

    entity->addComponent<SoundEffectComponent>(bodyMaterial, footMaterial, typeMaterial);
}


void EntityFactory::loadExplosionComponent(const json& componentData, std::shared_ptr<Entity> entity){

	float explosionAmount = componentData.value("explosionAmount", 0.0f);
    float explosionTime = componentData.value("explosionTime", 0.0f);

	entity->addComponent<ExplosionComponent>(explosionAmount, explosionTime);
}

void EntityFactory::loadClickableComponent(const json& componentData, std::shared_ptr<Entity> entity){

	float offsetX = componentData.value("offsetX", 0.0f);
    float offsetY = componentData.value("offsetY", 0.0f);
    float w = componentData.value("w", 0.0f);
    float h = componentData.value("h", 0.0f);
    std::string clickCommandType = componentData.value("commandType", "none");

	entity->addComponent<ClickableComponent>(offsetX, offsetY, w, h);

	auto clickComp = entity->getComponent<ClickableComponent>();

	if(!clickComp) return; 

	if(clickCommandType == "PlayGameCommand"){
		clickComp->clickCommand = std::make_unique<PlayGameCommand>(gameManager);
	}

	if(clickCommandType == "SelectCharacterCommand"){
		clickComp->clickCommand = std::make_unique<SelectCharacterCommand>(gameManager);
	}

}

void EntityFactory::loadTextLabelComponent(const json& componentData, std::shared_ptr<Entity> entity){

	std::string text = componentData.value("text", "Text here");
    std::string font = componentData.value("font", "ARCADECLASSIC.TTF");
    int size = componentData.value("size", 18);

	entity->addComponent<TextLabelComponent>(text, font, size);
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
    componentLoaders["MovementCommandComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadMovementCommandComponent(data, entity);
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
    componentLoaders["UITag"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadUITag(data, entity);
    };
    componentLoaders["TextTag"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadTextTag(data, entity);
    };
    componentLoaders["IMGTag"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadIMGTag(data, entity);
    };
    componentLoaders["HpBarTag"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadHpBarTag(data, entity);
    };
    componentLoaders["HpBarComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadHpBarComponent(data, entity);
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
    componentLoaders["ItemComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadItemComponent(data, entity);
    };
    componentLoaders["FloatingEffectComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadFloatingEffectComponent(data, entity);
    };
    componentLoaders["AbilityComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadAbilityComponent(data, entity);
    };
    componentLoaders["AIComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadAIComponent(data, entity);
    };
    componentLoaders["SpawnerComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadSpawnerComponent(data, entity);
    };   
    componentLoaders["HitboxComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadHitboxComponent(data, entity);
    };  
    componentLoaders["ShadowComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadShadowComponent(data, entity);
    };
    componentLoaders["ShakeEffectComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadShakeEffectComponent(data, entity);
    };    
    componentLoaders["SoundEffectComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadSoundEffectComponent(data, entity);
    };    
    componentLoaders["ExplosionComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadExplosionComponent(data, entity);
    };    
    componentLoaders["ClickableComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadClickableComponent(data, entity);
    }; 
    componentLoaders["TextLabelComponent"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadTextLabelComponent(data, entity);
    }; 
    componentLoaders["CoreTag"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadCoreTag(data, entity);
    }; 
    componentLoaders["BossTag"] = [this](const json& data, std::shared_ptr<Entity> entity) {
        this->loadBossTag(data, entity);
    }; 

    
    
}
