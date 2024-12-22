#include <iostream>
#include "ECS/EntityFactory.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "Components/Components.h"
#include "Systems/Systems.h"



void EntityFactory::createBackgroundEntity(const std::string& textureName){

	auto background = ecsManager->createEntity();
	background->addComponent<TransformComponent>();
	background->addComponent<SpriteComponent>(textureName, 1280, 800);
	
	ecsManager->setEntityName(background, "background");

}




void EntityFactory::createPlayerEntity(const SpawnRequest& req){

	auto player = ecsManager->createEntity();
	ecsManager->setEntityName(player, "player");
	player->addComponent<TransformComponent>(req.x, req.y);
	player->addComponent<SpriteComponent>("orc3", 64, 64, 2);
	player->addComponent<AnimationComponent>();
	player->addComponent<PlayableComponent>();
	player->addComponent<StateComponent>();
	player->addComponent<StatusComponent>(100, 100);
	player->addComponent<CooldownComponent>("basic_attack", 0.57f);
	auto animComp = player->getComponent<AnimationComponent>();

	
	    // 애니메이션을 JSON 파일에서 로드
    if (!animComp->loadAnimationsFromFile("assets/animations.json", animComp)) {
        std::cerr << "Failed to load animations for player." << std::endl;
    }
 	// 기본 애니메이션 설정
    animComp->playAnimation("d_idle");


    

	

}
    // ... 필요한 팩토리 메서드를 추가




void EntityFactory::createFarmerEntity(const SpawnRequest& req){

	auto farmer = ecsManager->createEntity();
	ecsManager->setEntityName(farmer, "farmer");
	farmer->addComponent<TransformComponent>(req.x, req.y);
	farmer->addComponent<SpriteComponent>("farmer", 21, 28, 3);
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

	Direction direction;
	direction.x = req.directionX;
	direction.y = req.directionY;

	slash->addComponent<AttackComponent>(req.damage);
	slash->addComponent<TransformComponent>(req.x, req.y, direction, req.scale);
	slash->addComponent<SpriteComponent>("water_tile", 100, 200);
	slash->addComponent<LifeTimeComponent>(req.duration);





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

