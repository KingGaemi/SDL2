#include "Systems/AnimationSystem.h"
#include "Components/DirectionComponent.h"
#include "Components/StateComponent.h"
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

                if(spriteComp && directComp && stateComp){

                	int hDir = directComp->direction.hDir;
                	int vDir = directComp->direction.vDir;

                    if(stateComp->currentState == States::Death){
                        if(vDir != 0){
                            if(vDir == 1){
                                if(animComp->currentAnimation != "d_death") animComp->playAnimation("d_death");
                            }
                            if(vDir == -1){
                                if(animComp->currentAnimation != "u_death") animComp->playAnimation("u_death");
                            }
                        }else{
                            if(hDir == -1){
                                if(animComp->currentAnimation != "l_death") animComp->playAnimation("l_death");
                            }
                            if (hDir == 1){
                                if(animComp->currentAnimation != "r_death") animComp->playAnimation("r_death");
                            }
                        }
                        if(animComp->currentAnimation == "d_death" || animComp->currentAnimation == "u_death" 
                            ||animComp->currentAnimation == "l_death" || animComp->currentAnimation == "r_death"){
                            animComp->busy =true;
                        }
                    }


                    if(!animComp->busy){
                        if(stateComp->currentState == States::Attack){
                            if(vDir != 0){
                                if(vDir == 1){
                                    if(stateComp->isWalking){
                                        animComp->playAnimation("d_walk_attack");
                                    }else if(stateComp->isRunning){
                                        animComp->playAnimation("d_run_attack");
                                    }else{
                                        animComp->playAnimation("d_attack");
                                    }
                                }
                                if(vDir == -1){
                                    if(stateComp->isWalking){
                                        animComp->playAnimation("u_walk_attack");
                                    }else if(stateComp->isRunning){
                                        animComp->playAnimation("u_run_attack");
                                    }else{
                                        animComp->playAnimation("u_attack");
                                    }
                                }
                            }else{
                                if(hDir == -1){
                                    if(stateComp->isWalking){
                                        animComp->playAnimation("l_walk_attack");
                                    }else if(stateComp->isRunning){
                                        animComp->playAnimation("l_run_attack");
                                    }else{
                                        animComp->playAnimation("l_attack");
                                    }
                                }
                                if (hDir == 1){
                                    if(stateComp->isWalking){
                                        animComp->playAnimation("r_walk_attack");
                                    }else if(stateComp->isRunning){
                                        animComp->playAnimation("r_run_attack");
                                    }else{
                                        animComp->playAnimation("r_attack");
                                    }
                                }
                            }
                            if(animComp->currentAnimation == "d_attack" || animComp->currentAnimation == "u_attack" 
                                ||animComp->currentAnimation == "l_attack" || animComp->currentAnimation == "r_attack"

                                ||animComp->currentAnimation == "d_walk_attack" || animComp->currentAnimation == "u_walk_attack" 
                                ||animComp->currentAnimation == "l_walk_attack" || animComp->currentAnimation == "r_walk_attack"

                                ||animComp->currentAnimation == "d_run_attack" || animComp->currentAnimation == "u_run_attack" 
                                ||animComp->currentAnimation == "l_run_attack" || animComp->currentAnimation == "r_run_attack"
                                ){
                                animComp->busy = true;
                            }   
                        }else if(stateComp->currentState == States::Hurt){
                            if(vDir != 0){
                                if(vDir == 1){
                                    if(animComp->currentAnimation != "d_hurt") animComp->playAnimation("d_hurt");
                                }
                                if(vDir == -1){
                                    if(animComp->currentAnimation != "u_hurt") animComp->playAnimation("u_hurt");
                                }
                            }else{
                                if(hDir == -1){
                                    if(animComp->currentAnimation != "l_hurt") animComp->playAnimation("l_hurt");
                                }
                                if (hDir == 1){
                                    if(animComp->currentAnimation != "r_hurt") animComp->playAnimation("r_hurt");
                                }
                            }
                            if(animComp->currentAnimation == "d_hurt" || animComp->currentAnimation == "u_hurt" 
                                ||animComp->currentAnimation == "l_hurt" || animComp->currentAnimation == "r_hurt"){
                                animComp->busy =true;
                            }
                        }else if(stateComp->currentState == States::Run){

                                if(vDir != 0){
                                    if(vDir == 1){
                                        if(animComp->currentAnimation != "d_run") animComp->playAnimation("d_run");
                                    }
                                    if(vDir == -1){
                                        if(animComp->currentAnimation != "u_run") animComp->playAnimation("u_run");
                                    }
                                }else{
                                    if(hDir == -1){
                                        if(animComp->currentAnimation != "l_run") animComp->playAnimation("l_run");
                                    }
                                    if (hDir == 1){
                                        if(animComp->currentAnimation != "r_run") animComp->playAnimation("r_run");
                                    }
                                }
                        }else if(stateComp->currentState == States::Idle){

                            if(hDir == -1){
                                if(animComp->currentAnimation != "l_idle") animComp->playAnimation("l_idle");
                            }
                            if (hDir == 1){
                                if(animComp->currentAnimation != "r_idle") animComp->playAnimation("r_idle");
                            }
                            if(vDir == 1){
                                if(animComp->currentAnimation != "d_idle") animComp->playAnimation("d_idle");
                            }
                            if(vDir == -1){
                                if(animComp->currentAnimation != "u_idle") animComp->playAnimation("u_idle");
                            }

                        }else if(stateComp->currentState == States::Walk){
                            if(vDir != 0){
                                if(vDir == 1){
                                    if(animComp->currentAnimation != "d_walk") animComp->playAnimation("d_walk");
                                }
                                if(vDir == -1){
                                    if(animComp->currentAnimation != "u_walk") animComp->playAnimation("u_walk");
                                }
                            }else{
                                if(hDir == -1){
                                    if(animComp->currentAnimation != "l_walk") animComp->playAnimation("l_walk");
                                }
                                if (hDir == 1){
                                    if(animComp->currentAnimation != "r_walk") animComp->playAnimation("r_walk");
                                }
                            }
                        }


                    }


                    if (animComp && spriteComp) {
                        updateAnimation(animComp, spriteComp, deltaTime);
                    }
                }
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

    

    float baseDuration = frame->duration;
    float duration;

    if(animData->type == "attack"){
        duration = baseDuration / animComp->attackFast;
    }else if(animData->type == "move"){
        duration = baseDuration / animComp->moveFast;
    }else{
        duration = baseDuration;
    }


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
        spriteComp->srcRect.x = frame->x;
        spriteComp->srcRect.y = frame->y;
        spriteComp->srcRect.w = frame->w;
        spriteComp->srcRect.h = frame->h;
    }
}


// void AnimationSystem::Init(){


//     json animations;

//     int startX = 0;
//     int gap = 64;
//     int frameCount = 4;
//     float duration = 0.2; 

//     // 예제: idle 애니메이션
//     animations["d_idle"] = createAnimation("d_idle", "idle", true, startX, 0, frameCount, gap, duration);
//     animations["u_idle"] = createAnimation("u_idle", "idle", true, startX, 64, frameCount, gap, duration);
//     animations["l_idle"] = createAnimation("l_idle", "idle", true, startX, 128, frameCount, gap, duration);
//     animations["r_idle"] = createAnimation("r_idle", "idle", true, startX, 192, frameCount, gap, duration);

//     startX += 64*frameCount;
//     duration = 0.125;
//     frameCount = 8;

//     animations["d_attack"] = createAnimation("d_attack", "attack", false, startX, 0, frameCount, gap, duration);
//     animations["u_attack"] = createAnimation("u_attack", "attack", false, startX, 64, frameCount, gap, duration);
//     animations["l_attack"] = createAnimation("l_attack", "attack", false, startX, 128, frameCount, gap, duration);
//     animations["r_attack"] = createAnimation("r_attack", "attack", false, startX, 192, frameCount, gap, duration);

//     startX += 64*frameCount;
//     duration = 0.04;
//     frameCount = 6;

//     animations["d_hurt"] = createAnimation("d_hurt", "hurt", false, startX, 0, frameCount, gap, duration);
//     animations["u_hurt"] = createAnimation("u_hurt", "hurt", false, startX, 64, frameCount, gap, duration);
//     animations["l_hurt"] = createAnimation("l_hurt", "hurt", false, startX, 128, frameCount, gap, duration);
//     animations["r_hurt"] = createAnimation("r_hurt", "hurt", false, startX, 192, frameCount, gap, duration);

//     startX += 64 * frameCount;
//     duration = 0.125;
//     frameCount = 8;

//     animations["d_death"] = createAnimation("d_death", "death", false, startX, 0, frameCount, gap, duration);
//     animations["u_death"] = createAnimation("u_death", "death", false, startX, 64, frameCount, gap, duration);
//     animations["l_death"] = createAnimation("l_death", "death", false, startX, 128, frameCount, gap, duration);
//     animations["r_death"] = createAnimation("r_death", "death", false, startX, 192, frameCount, gap, duration);


    
//     startX += 64*frameCount;
//     duration = 0.1666;
//     frameCount = 6;

//     animations["d_walk"] = createAnimation("d_walk", "move", true, startX, 0, frameCount, gap, duration);
//     animations["u_walk"] = createAnimation("u_walk", "move", true, startX, 64, frameCount, gap, duration);
//     animations["l_walk"] = createAnimation("l_walk", "move", true, startX, 128, frameCount, gap, duration);
//     animations["r_walk"] = createAnimation("r_walk", "move", true, startX, 192, frameCount, gap, duration);


    
//     startX += 64*frameCount;
//     duration = 0.1666;
//     frameCount = 6;

//     animations["d_walk_attack"] = createAnimation("d_walk_attack", "attack", false, startX, 0, frameCount, gap, duration);
//     animations["u_walk_attack"] = createAnimation("u_walk_attack", "attack", false, startX, 64, frameCount, gap, duration);
//     animations["l_walk_attack"] = createAnimation("l_walk_attack", "attack", false, startX, 128, frameCount, gap, duration);
//     animations["r_walk_attack"] = createAnimation("r_walk_attack", "attack", false, startX, 192, frameCount, gap, duration);
    
    
//     startX += 64*frameCount;
//     duration = 0.125;
//     frameCount = 8;

//     animations["d_run"] = createAnimation("d_run", "move", true, startX, 0, frameCount, gap, duration);
//     animations["u_run"] = createAnimation("u_run", "move", true, startX, 64, frameCount, gap, duration);
//     animations["l_run"] = createAnimation("l_run", "move", true, startX, 128, frameCount, gap, duration);
//     animations["r_run"] = createAnimation("r_run", "move", true, startX, 192, frameCount, gap, duration);


    
//     startX += 64*frameCount;
//     duration = 0.125;
//     frameCount = 8;

//     animations["d_run_attack"] = createAnimation("d_run_attack", "attack", false, startX, 0, frameCount, gap, duration);
//     animations["u_run_attack"] = createAnimation("u_run_attack", "attack", false, startX, 64, frameCount, gap, duration);
//     animations["l_run_attack"] = createAnimation("l_run_attack", "attack", false, startX, 128, frameCount, gap, duration);
//     animations["r_run_attack"] = createAnimation("r_run_attack", "attack", false, startX, 192, frameCount, gap, duration);
    
//     std::ofstream outFile("assets/animations.json");
//     outFile << animations.dump(4);  // JSON 데이터를 예쁘게 포맷해서 저장
//     outFile.close();
    
// }



// json AnimationSystem::createAnimation(const std::string& name, const std::string& type, bool loop,
//                      int startX, int startY, int frameCount, int gap, float duration) {
//     json animation;
//     animation["type"] = type;
//     animation["loop"] = loop;

//     // 프레임 생성
//     for (int i = 0; i < frameCount; ++i) {
//         animation["frames"].push_back({
//             {"x", startX + i * gap},
//             {"y", startY},
//             {"w", gap},
//             {"h", gap},
//             {"duration", duration}
//         });
//     }

//     return animation;
// }


