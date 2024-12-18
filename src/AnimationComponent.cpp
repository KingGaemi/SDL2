#include "Components/AnimationComponent.h"
#include <fstream>


void AnimationComponent::playAnimation(const std::string animName){
		if (animations.find(animName) != animations.end()) {
            currentAnimation = animName;
            currentFrameIndex = 0;
            currentTime = 0.0f;
        }else{
        	std::cout << "Has no Animation named:" << animName << "." << std::endl;
        }

}

AnimationData* AnimationComponent::getCurrentAnimationData() {
		auto it = animations.find(currentAnimation);
		if(it != animations.end()){
			return &it->second;
		}
		return nullptr;
}

AnimationFrame* AnimationComponent::getCurrentFrame(){
		AnimationData* data = getCurrentAnimationData();
        if (data && currentFrameIndex >= 0 && currentFrameIndex < (int)data->frames.size()) {
            return &data->frames[currentFrameIndex];
        }
        return nullptr;
}




bool AnimationComponent::loadAnimationsFromFile(const std::string& filename, std::shared_ptr<AnimationComponent> animComp) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return false;
    }

    json j;
    file >> j;

    // j["animations"] 객체 접근
    if (!j.contains("animations")) {
        std::cerr << "No 'animations' field in " << filename << std::endl;
        return false;
    }

    auto animationsJson = j["animations"];

    for (auto it = animationsJson.begin(); it != animationsJson.end(); ++it) {
        std::string animName = it.key();
        json animDataJson = it.value();

        AnimationData animData;
        animData.name = animName;
        animData.loop = animDataJson.value("loop", true);

        if (!animDataJson.contains("frames")) {
            std::cerr << "No frames for animation " << animName << std::endl;
            continue;
        }

        for (auto& frameJson : animDataJson["frames"]) {
            int x = frameJson.value("x", 0);
            int y = frameJson.value("y", 0);
            int w = frameJson.value("w", 64);
            int h = frameJson.value("h", 64);
            float duration = frameJson.value("duration", 0.1f);
            animData.frames.push_back({x, y, w, h, duration});
        }

        animComp->animations[animName] = animData;
    }

    return true;
}