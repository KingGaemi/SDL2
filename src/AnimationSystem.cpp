#include "Systems/AnimationSystem.h"
#include "Components/DirectionComponent.h"
#include "Components/StateComponent.h"
#include "Components/ItemComponent.h"
#include "Components/ProjectileComponent.h"
#include <iostream>
#include <fstream>




void AnimationSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

   	for (auto& entity : entities) {

        if(entity->isActive && entity->hasComponent<AnimationComponent>()){
            auto animComp = entity->getComponent<AnimationComponent>();
            if(animComp){
                auto spriteComp = entity->getComponent<SpriteComponent>();
                auto directComp = entity->getComponent<DirectionComponent>();
                auto stateComp = entity->getComponent<StateComponent>();
                auto itemComp = entity->getComponent<ItemComponent>();
                auto projectileComp = entity->getComponent<ProjectileComponent>();
                // Unit or Objects
                if(spriteComp && directComp && stateComp){

                	int hDir = directComp->direction.hDir;
                	int vDir = directComp->direction.vDir;
                    std::string animName = "";

                    if(spriteComp->hasDirectional){
                        if(vDir != 0){
                            if(vDir == 1){
                               animName += "d";
                            }
                            if(vDir == -1){
                                animName += "u";
                            }
                        }else{
                            if(hDir == -1){
                                animName += "l";
                            }
                            if (hDir == 1){
                                animName += "r";
                            }
                        }
                        if(vDir == 0 && hDir == 0) animName += "d";
                    }

                    if(stateComp->actionState == ActionStates::Death){
                        animName += "_death";
                        if(animComp->currentAnimation == "d_death" || animComp->currentAnimation == "u_death" 
                            ||animComp->currentAnimation == "l_death" || animComp->currentAnimation == "r_death"){                        
                        }else{
                            animComp->playAnimation(animName);
                            animComp->busy =true;
                            animComp->lock = true;
                        }
                    }

                    if(!animComp->busy){
                        if(stateComp->movementState == MovementStates::Stop &&
                            stateComp->actionState == ActionStates::Idle) animName += "_idle";
                        else if(stateComp->movementState == MovementStates::Walk) animName += "_walk";
                        else if(stateComp->movementState == MovementStates::Run) animName += "_run";

                        if(stateComp->actionState == ActionStates::Attack || stateComp->actionState == ActionStates::Cast){
                            animName += "_attack";
                            animComp->busy = true;
                        }
                        if(stateComp->actionState == ActionStates::Hurt){
                            animName += "_hurt";
                            animComp->busy = true;
                        }
                        if(animComp->currentAnimation == animName && animComp->animations[animName].loop) {

                        }else{
                            animComp->playAnimation(animName);
                        }
                    }

                    if (animComp && spriteComp && stateComp) {
                        updateAnimation(animComp, spriteComp, deltaTime);
                        if(animComp->isAnimationComplete()) stateComp->inMotion = false;
                    }
                }

                // projectiles

                if(spriteComp && directComp && projectileComp){
                    if(animComp->currentAnimation != "default") animComp->playAnimation("default");
                    updateAnimation(animComp, spriteComp, deltaTime);
                }
            }
        }
    }
}




void AnimationSystem::updateAnimation(std::shared_ptr<AnimationComponent> animComp, std::shared_ptr<SpriteComponent> spriteComp, float deltaTime){

	AnimationData* animData = animComp->getCurrentAnimationData();
    if (!animData || animData->frames.empty()) return;
    if(!animComp || !spriteComp) return;
    // 현재 프레임
    FrameData* frame = animComp->getCurrentFrame();
    if (!frame) return;

    // 경과 시간 갱신
    animComp->currentTime += deltaTime;

    float baseDuration = frame->duration;
    float duration;

    if(animData->type == "attack"){
        duration = baseDuration / animComp->attackFast;
    }else if(animData->type == "move"){
        duration = baseDuration / animComp->moveFast;
    }else{
        duration = baseDuration;
    }

    // temp
    duration *= 1.2f;

    // 현재 프레임 지속시간보다 경과 시간이 길다면 다음 프레임으로
    if (animComp->currentTime >= duration) {
        animComp->currentTime -= duration;
        animComp->currentFrameIndex++;
        // 프레임 넘어갔을 때 애니메이션 루프 처리
        if (animComp->currentFrameIndex >= (int)animData->frames.size()) {
            if (animData->loop) {
                animComp->currentFrameIndex = 0;

            } else {
                // 루프 안하는 애니메이션이면 마지막 프레임 유지
                animComp->currentFrameIndex = (int)animData->frames.size() - 1;
                animComp->busy = false;
                // std::cout << duration << std::endl;
            }
        }
        frame = animComp->getCurrentFrame(); // 새 프레임 정보 갱신
    }

    // spriteComp에 현재 프레임 정보 반영
    if (frame) {
        if(spriteComp->textureId == "unknown"){
            // std::cout <<"texture is unknown" << std::endl;
            spriteComp->srcRect.x = 0;
            spriteComp->srcRect.y = 0;
            spriteComp->srcRect.w = 32;
            spriteComp->srcRect.h = 32;            
        }else{            
            spriteComp->srcRect.x = frame->x;
            spriteComp->srcRect.y = frame->y;
            spriteComp->srcRect.w = frame->w;
            spriteComp->srcRect.h = frame->h;
        }
    }
}





