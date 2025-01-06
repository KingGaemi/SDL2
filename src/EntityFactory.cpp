#include <iostream>
#include "ECS/EntityFactory.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "Components/Components.h"

#include "Groups.h"



void EntityFactory::createBackgroundEntity(const std::string& textureName){

	auto background = ecsManager->createEntity();
	background->addComponent<PositionComponent>(640, 400);
	background->addComponent<SpriteComponent>(textureName, 1280, 800);
	background->addComponent<SceneTag>(SceneCode::Menu);
	background->addComponent<IMGTag>();

	
	ecsManager->setEntityName(background, "background");

}




void EntityFactory::createPlayerEntity(const SpawnRequest& req){


	auto player = ecsManager->createEntity();
	ecsManager->setEntityName(player, "player");

	generalUnit(player, req);
	player->addComponent<PlayerTag>();
	player->addComponent<PlayableComponent>();
	player->addComponent<DashComponent>(0.2f);
	player->addComponent<SpriteComponent>("orc3", 64, 64, 2.0f);

	player->addComponent<StatusComponent>(100, 100);


	player->addComponent<PhysicsComponent>(BodyType::Dynamic);


	auto colComp = player->getComponent<ColliderComponent>();
	colComp->offsetX = -1.0f;
	colComp->offsetY = -6.0f;

	auto statusComp = player->getComponent<StatusComponent>();
	player->addComponent<CooldownComponent>("attack", 1.0f/statusComp->attackSpeed);
	player->addComponent<CommandComponent>();

	auto animComp = player->getComponent<AnimationComponent>();
	animComp->attackFast = statusComp->attackSpeed;
	animComp->moveFast =  statusComp->movementSpeed / 100.0f;
	
	// 애니메이션을 JSON 파일에서 로드
    if (!animComp->loadAnimationsFromFile("assets/animations.json", animComp)) {
        std::cerr << "Failed to load animations for player." << std::endl;
    }
 	// 기본 애니메이션 설정
    animComp->playAnimation("d_idle");


}
    
void EntityFactory::createEri(const SpawnRequest& req){

	int w = 31;
	int h = 38;
	float sc = 2.0f;
	std::string name = "eri";

	auto eri = ecsManager->createEntity();

	eri->addComponent<SceneTag>(SceneCode::Game);

	eri->addComponent<PositionComponent>(req.x, req.y);
	// eri->addComponent<VelocityComponent>(5.0f, 5.0f);

	eri->addComponent<PhysicsComponent>(BodyType::Dynamic);
	eri->addComponent<SpriteComponent>(name, w, h, sc);
	eri->addComponent<ColliderComponent>(w*sc, h*sc, "eri");
	eri->addComponent<TransformComponent>(w, h, sc);
	eri->addComponent<TeamComponent>(req.teamCode);
	eri->addComponent<StatusComponent>(100, 100);
	



	ecsManager->setEntityName(eri, "eri");

}



void EntityFactory::createBox(const SpawnRequest& req){

	int w = 32;
	int h = 32;
	float sc = 2.0f;
	std::string name = "box1";

	auto box = ecsManager->createEntity();

	box->addComponent<SceneTag>(SceneCode::Game);
	box->addComponent<PositionComponent>(req.x, req.y);
	// eri->addComponent<VelocityComponent>(5.0f, 5.0f);
	box->addComponent<PhysicsComponent>(BodyType::Dynamic);
	box->addComponent<SpriteComponent>(name, w, h, sc);
	// box->addComponent<ColliderComponent>(w*sc, h*sc, "box");
	box->addComponent<TransformComponent>(w, h, sc);

	ecsManager->setEntityName(box, "box");

}

void EntityFactory::createGround(){

	int w = 1000;
	int h = 16;
	float sc = 2.0f;

	std::string name = "dirt_tile";

	auto ground = ecsManager->createEntity();

	ground->addComponent<SceneTag>(SceneCode::Game);
	ground->addComponent<PositionComponent>(600, 800);
	// eri->addComponent<VelocityComponent>(5.0f, 5.0f);
	ground->addComponent<PhysicsComponent>(BodyType::Static);
	ground->addComponent<SpriteComponent>(name, w, h, sc);
	ground->addComponent<TransformComponent>(w, h, sc);

	ecsManager->setEntityName(ground, "ground");


}



void EntityFactory::createFarmerEntity(const SpawnRequest& req){

	auto farmer = ecsManager->createEntity();
	ecsManager->setEntityName(farmer, "farmer");

	farmer->addComponent<SceneTag>(SceneCode::Game);
	farmer->addComponent<PositionComponent>(req.x, req.y);
	farmer->addComponent<VelocityComponent>();
	farmer->addComponent<DirectionComponent>(0, 1);
	farmer->addComponent<SpriteComponent>("farmer", 21, 28, 3);
	farmer->addComponent<ColliderComponent>(21*3, 28*3, "farmer");
	farmer->addComponent<AnimationComponent>();
	farmer->addComponent<StateComponent>();




	auto animComp = farmer->getComponent<AnimationComponent>();


	auto stateComp = farmer->getComponent<StateComponent>();
	stateComp->currentState = States::Idle;



	int currentPoint;
	int nextPoint;

	AnimationData d_idleAnim;

	d_idleAnim.name = "d_idle";
	nextPoint = addAnimationFrames(d_idleAnim, 13, 4, 21, 28, 0.2f, 48, 4);
	currentPoint = nextPoint;
	d_idleAnim.loop = true;
	animComp->animations["d_idle"] = d_idleAnim;


	AnimationData d_specialAnim;
	d_specialAnim.name = "d_special";
	nextPoint = addAnimationFrames(d_specialAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	d_specialAnim.loop = true;
	animComp->animations["d_special"] = d_specialAnim;


	AnimationData d_walkAnim;
	d_walkAnim.name = "d_walk";
	nextPoint = addAnimationFrames(d_walkAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	d_walkAnim.loop = true;
	animComp->animations["d_walk"] = d_walkAnim;


	AnimationData s_idleAnim;
	s_idleAnim.name = "s_idle";
	nextPoint = addAnimationFrames(s_idleAnim, currentPoint, 4, 21, 28, 0.2f, 48, 4);
	currentPoint = nextPoint;
	s_idleAnim.loop = true;
	animComp->animations["s_idle"] = s_idleAnim;


	AnimationData s_specialAnim;
	s_specialAnim.name = "s_special";
	nextPoint = addAnimationFrames(s_specialAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	s_specialAnim.loop = true;
	animComp->animations["s_special"] = s_specialAnim;


	AnimationData s_walkAnim;
	s_walkAnim.name = "s_walk";
	nextPoint = addAnimationFrames(s_walkAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	s_walkAnim.loop = true;
	animComp->animations["s_walk"] = s_walkAnim;



	AnimationData u_walkAnim;
	u_walkAnim.name = "u_walk";
	nextPoint = addAnimationFrames(u_walkAnim, currentPoint, 4, 21, 28, 0.2f, 48, 4);
	currentPoint = nextPoint;
	u_walkAnim.loop = true;
	animComp->animations["u_walk"] = u_walkAnim;


	AnimationData u_specialAnim;
	u_specialAnim.name = "u_special";
	nextPoint = addAnimationFrames(u_specialAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	u_specialAnim.loop = true;
	animComp->animations["u_special"] = u_specialAnim;


	AnimationData u_idleAnim;
	u_idleAnim.name = "u_idle";
	nextPoint = addAnimationFrames(u_idleAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	u_idleAnim.loop = true;
	animComp->animations["u_idle"] = u_idleAnim;


	animComp->playAnimation("d_idle");


}


void EntityFactory::createEnemyDummy(const SpawnRequest& req){

	auto enemy = ecsManager->createEntity();
	ecsManager->setEntityName(enemy, "enemy");

	generalUnit(enemy, req);
	enemy->addComponent<Player2Tag>();
	enemy->addComponent<DashComponent>(0.2f);
	enemy->addComponent<SpriteComponent>("orc3", 64, 64, 2.0f);
	enemy->addComponent<StatusComponent>(100, 100);
	enemy->addComponent<PhysicsComponent>(BodyType::Dynamic);


	auto colComp = enemy->getComponent<ColliderComponent>();
	colComp->offsetX = -1.0f;
	colComp->offsetY = -6.0f;

	auto statusComp = enemy->getComponent<StatusComponent>();
	enemy->addComponent<CooldownComponent>("attack", 1.0f/statusComp->attackSpeed);

	enemy->addComponent<CommandComponent>();
	
	auto animComp = enemy->getComponent<AnimationComponent>();
	animComp->attackFast = statusComp->attackSpeed;
	animComp->moveFast =  statusComp->movementSpeed / 100.0f;
	
	// 애니메이션을 JSON 파일에서 로드
    if (!animComp->loadAnimationsFromFile("assets/animations.json", animComp)) {
        std::cerr << "Failed to load animations for player." << std::endl;
    }
 	// 기본 애니메이션 설정
    // animComp->playAnimation("d_idle");
	
	// 애니메이션을 JSON 파일에서 로드
    if (!animComp->loadAnimationsFromFile("assets/animations.json", animComp)) {
        std::cerr << "Failed to load animations for player." << std::endl;
    }
 	// 기본 애니메이션 설정
    animComp->playAnimation("d_idle");
}

void EntityFactory::createText(const SpawnRequest& req){

	auto text = ecsManager->createEntity();
	text->addComponent<PositionComponent>(req.x, req.y);
	text->addComponent<SpriteComponent>("font", req.x, req.y);
	text->addComponent<UITag>();

	ecsManager->setEntityName(text, "text");

}

int EntityFactory::addAnimationFrames(AnimationData& animData, int x, int y, int w, int h, float duration, int interval, int count){

	int desX = x;
	int desY = y;

	for (int i = 0; i < count; ++i)
	{
		desX = x + (interval * i);
		animData.frames.push_back({desX, desY, w, h, duration});
	}

	return x + (interval * count);
}

void EntityFactory::createSlashEntity(const AttackRequest& req){

	auto slash = ecsManager->createEntity();

	slash->addComponent<AttackComponent>(req.damage);
	slash->addComponent<PositionComponent>(req.x, req.y);
	slash->addComponent<DirectionComponent>(req.hDir, req.vDir);
	slash->addComponent<SpriteComponent>("water_tile", 100, 200, req.scale);
	slash->addComponent<LifeTimeComponent>(req.duration);
	slash->addComponent<ColliderComponent>(100, 200, "slash");
	slash->addComponent<TeamComponent>(TeamCode::Ally);

}

void EntityFactory::generalUnit(std::shared_ptr<Entity> entity, const SpawnRequest& req){

	entity->addComponent<SceneTag>(SceneCode::Game);
	entity->addComponent<TeamComponent>(req.teamCode);
	entity->addComponent<PositionComponent>(req.x, req.y);
	entity->addComponent<DirectionComponent>(0, 1);
	entity->addComponent<VelocityComponent>();
	entity->addComponent<TransformComponent>(req.w, req.h, req.sc);
	entity->addComponent<ColliderComponent>(req.w*req.sc, req.h*req.sc, req.type);
	entity->addComponent<AnimationComponent>();
	entity->addComponent<StateComponent>();
	entity->addComponent<SolidComponent>();

}




// void EntityFactory::createAttack(std::shared_ptr<ECSManager> ecsManager, float x, float y){

// 	auto attack = ecsManager->createEntity();
// 	attack->addComponent<TransformComponent>(x, y);
// 	attack->addComponent<SpriteComponent>("water_tile", 20, 40);
// 	attack->addComponent<LifeTimeComponent>();
	
// 	auto lifeComp = attack->getComponent<LifeTimeComponent>();

// 	if(lifeComp){
// 		lifeComp->lifeTime = 0.56f;
// 	}


// }

