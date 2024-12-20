#include "Systems/AnimationSystem.h"
#include <iostream>




void AnimationSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

   	for (auto& entity : entities) {

        auto animComp = entity->getComponent<AnimationComponent>();
        auto spriteComp = entity->getComponent<SpriteComponent>();
       	auto trans = entity->getComponent<TransformComponent>();
        auto state = entity->getComponent<StateComponent>();

        if(spriteComp && trans && animComp && state){

        	int dirX = trans->direction.x;
        	int dirY = trans->direction.y;


            if(animComp->busy){

                if(state->stateTimer < 0){
                    std::cout << "AnimationComplete" << std::endl;
                    animComp->busy = false;
                    state->currentState = States::Idle;
                }
            }




            if(!animComp->busy){


                if(state->currentState == States::Attack){
                    animComp->busy = true;
                    if(dirX == -1){
                        if(animComp->currentAnimation != "l_attack") animComp->playAnimation("l_attack");
                    }
                    if (dirX == 1){
                        if(animComp->currentAnimation != "r_attack") animComp->playAnimation("r_attack");
                    }
                    if(dirY == 1){
                        if(animComp->currentAnimation != "d_attack") animComp->playAnimation("d_attack");
                    }
                    if(dirY == -1){
                        if(animComp->currentAnimation != "u_attack") animComp->playAnimation("u_attack");
                    }
                }



                
                if(state->currentState == States::Run){
                    if(dirX == -1){
                        if(animComp->currentAnimation != "l_run") animComp->playAnimation("l_run");
                    }
                    if (dirX == 1){
                        if(animComp->currentAnimation != "r_run") animComp->playAnimation("r_run");
                    }
                    if(dirY == 1){
                        if(animComp->currentAnimation != "d_run") animComp->playAnimation("d_run");
                    }
                    if(dirY == -1){
                        if(animComp->currentAnimation != "u_run") animComp->playAnimation("u_run");
                    }
                }
                if(state->currentState == States::Idle){
                    if(dirX == -1){
                        if(animComp->currentAnimation != "l_idle") animComp->playAnimation("l_idle");
                    }
                    if (dirX == 1){
                        if(animComp->currentAnimation != "r_idle") animComp->playAnimation("r_idle");
                    }
                    if(dirY == 1){
                        if(animComp->currentAnimation != "d_idle") animComp->playAnimation("d_idle");
                    }
                    if(dirY == -1){
                        if(animComp->currentAnimation != "u_idle") animComp->playAnimation("u_idle");
                    }
                } 


                if(state->currentState == States::Walk){
                    if(dirX == -1){
                        if(animComp->currentAnimation != "l_walk") animComp->playAnimation("l_walk");
                    }
                    if (dirX == 1){
                        if(animComp->currentAnimation != "r_walk") animComp->playAnimation("r_walk");
                    }
                    if(dirY == 1){
                        if(animComp->currentAnimation != "d_walk") animComp->playAnimation("d_walk");
                    }
                    if(dirY == -1){
                        if(animComp->currentAnimation != "u_walk") animComp->playAnimation("u_walk");
                    }
                }


            }
            if (animComp && spriteComp) {
                updateAnimation(animComp, spriteComp, deltaTime);
            }
        }
    }
}


void AnimationSystem::updateAnimation(std::shared_ptr<AnimationComponent> animComp, std::shared_ptr<SpriteComponent> spriteComp, float deltaTime){

	AnimationData* animData = animComp->getCurrentAnimationData();
    if (!animData || animData->frames.empty()) return;

    // 현재 프레임
    AnimationFrame* frame = animComp->getCurrentFrame();
    if (!frame) return;

    // 경과 시간 갱신
    animComp->currentTime += deltaTime;

    // 현재 프레임 지속시간보다 경과 시간이 길다면 다음 프레임으로
    if (animComp->currentTime >= frame->duration) {
        animComp->currentTime -= frame->duration;
        animComp->currentFrameIndex++;
        // 프레임 넘어갔을 때 애니메이션 루프 처리
        if (animComp->currentFrameIndex >= (int)animData->frames.size()) {
            if (animData->loop) {
                animComp->currentFrameIndex = 0;
            } else {
                // 루프 안하는 애니메이션이면 마지막 프레임 유지
                animComp->currentFrameIndex = (int)animData->frames.size() - 1;
            }
        }
        frame = animComp->getCurrentFrame(); // 새 프레임 정보 갱신
    }

    // spriteComp에 현재 프레임 정보 반영
    if (frame) {
        spriteComp->srcRect.x = frame->x;
        spriteComp->srcRect.y = frame->y;
        spriteComp->srcRect.w = frame->w;
        spriteComp->srcRect.h = frame->h;
    }
}