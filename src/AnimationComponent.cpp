#include "Components/AnimationComponent.h"
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <regex>

void AnimationComponent::playAnimation(const std::string& animName){
    if(!lock){
		if (animations.find(animName) != animations.end()) {
            currentAnimation = animName;
            currentFrameIndex = 0;
            currentTime = 0.0f;
        }else{
        	std::cout << "Has no Animation named:" << animName << "." << std::endl;
            currentAnimation = "default";
            currentFrameIndex = 0;
            currentTime = 0.0f;
        }
    }

}

AnimationData* AnimationComponent::getCurrentAnimationData() {
		auto it = animations.find(currentAnimation);
		if(it != animations.end()){
			return &it->second;
		}
		return nullptr;
}

FrameData* AnimationComponent::getCurrentFrame(){
		AnimationData* data = getCurrentAnimationData();
        if (data && currentFrameIndex >= 0 && currentFrameIndex < (int)data->frames.size()) {
            return &data->frames[currentFrameIndex];
        }
        return nullptr;
}

bool AnimationComponent::loadAnimationsFromFile()
{

    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "[AnimationComp] Failed to open JSON: " << filename << "\n";
        return false;
    }

    nlohmann::ordered_json j = ordered_json::parse(file);
     
    file.close();

    if(!j.contains("frames") || !j["frames"].is_object()) {
        std::cerr << "[AnimationComp] JSON has no valid 'frames' object\n";
        return false;
    }
    auto& framesJson = j["frames"];
    // std::cout << j["frames"].begin().value()["duration"] << std::endl;   
    // std::cout << j["frames"].begin().value()["frame"].value("y", 10) << std::endl;
    // 2) "frames"를 삽입 순서대로 framesVec에 저장
    //    nlohmann::json 3.9.0+에서, 객체 순회는 삽입 순서를 보장
    std::vector<FrameData> framesVec;
    framesVec.reserve(framesJson.size());

    // for (const auto& [key, value] : framesJson.items()) {
    //     std::cout << "Index " << index 
    //               << " => key=\"" << key << "\", value=" << value << "\n";
    //     index++;
    // }

    // 디버그 출력
    // std::cout << "==== loadFrames insertion order ====\n";

    int index = 0;
    for (auto it = framesJson.begin(); it != framesJson.end(); ++it) {
        // it.key() 예) "orc1 #u_attack 0.aseprite"
        auto frameObj = it.value();
        if (!frameObj.contains("frame")) {
            std::cerr << "[Warn] No 'frame' in " << it.key() << "\n";
            continue;
        }
        auto rect = frameObj["frame"];
        int x = rect.value("x", 0);
        int y = rect.value("y", 0);
        int w = rect.value("w", 0);
        int h = rect.value("h", 0);

        float durationSec = 0.1f;
        if(frameObj.contains("duration")) {
            float ms = frameObj["duration"].get<float>(); // ms 단위
            durationSec = ms / 1000.f;                    // 초 단위
        }

        framesVec.push_back({x, y, w, h, durationSec});

        // 디버그
        // std::cout << " Index " << index 
        //           << " => key=\"" << it.key() << "\", x=" << x
        //           << ",y="<< y << ",w="<< w << ",h="<<h
        //           << ",dur=" << durationSec << "s\n";
        index++;
    }
    // std::cout << "Total frames read: " << framesVec.size() << "\n\n";

    // 3) frameTags 파싱
    if(!j.contains("meta") || !j["meta"].contains("frameTags")) {
        std::cerr << "[AnimationComp] No 'meta.frameTags'\n";
        return false;
    }
    auto& frameTags = j["meta"]["frameTags"];
    if(!frameTags.is_array()) {
        std::cerr << "[AnimationComp] 'frameTags' is not array\n";
        return false;
    }

    // std::cout << "==== load frameTags ====\n";
    for (auto& tag : frameTags) {
        // ex) { "name":"u_attack", "from":0, "to":8, "direction":"forward", "repeat":"1", ... }
        std::string animName = tag.value("name","none");
        int fromIndex = tag.value("from",0);
        int toIndex   = tag.value("to",0);
        std::string repeatVal = tag.value("repeat","0"); // "0"=loop, "1"=once ?
        std::string type = tag.value("type", "default");

        bool reverse = (tag.value("direction", "default") == "reverse");

        // AnimationData 생성
        AnimationData animData;
        animData.name = animName;
        // 예) repeat="1"이면 한번만 재생, repeat="0"이면 무한재생
        // => 프로젝트 규칙에 맞게 결정
        animData.loop = (repeatVal == "1") ? false : true;
        animData.type = type;
        animData.reverse = reverse;
        // fromIndex~toIndex 범위 체크
        if(fromIndex<0) fromIndex=0;
        if(toIndex >= (int)framesVec.size()){
            toIndex = (int)framesVec.size()-1;
        }
        if(fromIndex>toIndex) {
            std::cerr<<"[Warn] Tag '"<<animName<<"' invalid range: "<<fromIndex<<"->"<<toIndex<<"\n";
            continue;
        }

        // framesVec에서 해당 구간 프레임 복사
        for (int i=fromIndex; i<=toIndex; i++){
            animData.frames.push_back(framesVec[i]);
        }

        animations[animName] = animData;

        // 디버그
        // std::cout << " Anim \"" << animName << "\": from=" << fromIndex 
        //           << ",to=" << toIndex << ", totalFrames=" << animData.frames.size()
        //           << (animData.loop ? ", loop\n" : ", once\n");
    }

    return true;
}

bool AnimationComponent::isAnimationComplete() const {
    if (animations.find(currentAnimation) != animations.end()) {
        return !animations.at(currentAnimation).loop && 
               currentFrameIndex >= static_cast<int>(animations.at(currentAnimation).frames.size());
    }
    return true;
}

int AnimationComponent::extractFrameIndex(const std::string& key) {
    // 정규식: 끝에 " (숫자).aseprite" 형태 추출
    static std::regex re(R"(.*\s(\d+)\.aseprite$)");
    std::smatch match;
    if (std::regex_match(key, match, re)) {
        return std::stoi(match[1].str());
    }
    return 0; // 못 찾으면 0
}



// json AnimationComponent::createAnimation(const std::string& name, const std::string& type, bool loop,
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




