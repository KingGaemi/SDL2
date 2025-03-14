#include "Manager/SoundManager.h"



bool SoundManager::loadMusic(const std::string& musicID, std::string_view p_filePath){
        std::string pathStr(p_filePath);
		Mix_Music* music = Mix_LoadMUS(pathStr.c_str());
	    if (!music) {
	        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
	        return false;
	    }
		musics[musicID] = music;
		return true;
	}

bool SoundManager::loadEffect(const std::string& effectID, std::string_view p_filePath){
    std::string pathStr(p_filePath);
	Mix_Chunk* effect = Mix_LoadWAV(pathStr.c_str());
    if (!effect) {
        std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
        return false;
    }
	effects[effectID] = effect;
	return true;
}


 	// 배경 음악 재생 (-1 = 무한 반복)
bool SoundManager::playMusic(const std::string& musicID, int loops) {
    auto it = musics.find(musicID);
    if (it != musics.end()) {
        if (Mix_PlayMusic(it->second, loops) == -1) {
            std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
            return false;
        }
        return true;
    }
    std::cerr << "Music not found: " << musicID << std::endl;
    return false;
}

    // 효과음 재생 (채널 -1 = 사용 가능한 첫 번째 채널, 0 = 반복 없음)
bool SoundManager::playEffect(const std::string& effectID, int loops) {
    auto it = effects.find(effectID);
    if (it != effects.end()) {
        if (Mix_PlayChannel(-1, it->second, loops) == -1) {
            std::cerr << "Failed to play sound effect: " << Mix_GetError() << std::endl;
            return false;
        }
        return true;
    }
    std::cerr << "Effect not found: " << effectID << std::endl;
    return false;
}


bool SoundManager::playABSound(const std::string& A, const std::string& B, const std::string& behavior) {
    SoundSet key{A, B, behavior};
    auto it = soundMap.find(key);
    if (it != soundMap.end()) {
        std::cout << "Playing sound: " << it->second.soundId << " with volume: " << it->second.volume << std::endl;
        return true;
    }

    std::cerr << "Sound not found for (" << A << ", " << B << ", " << behavior << ")" << std::endl;
    return false;
    
}



bool SoundManager::registerEffects(){
    Mix_AllocateChannels(64);
	std::ifstream file("json/sound/sound_set.json");
    if(!file.is_open()) {
        std::cerr << "[SoundManager] Failed to open JSON: " << "json/sound/sound_set.json" << "\n";
        return false;
    }

    nlohmann::ordered_json fj = nlohmann::ordered_json::parse(file); 
    file.close();


    for(auto& j : fj["sound_sets"]){

        if(!j.contains("A") || !j["A"].is_object()) {
            std::cerr << "JSON has no valid A \n";
            return false;
        }
        auto& Material_A = j["A"];


        if(!j.contains("B") || !j["B"].is_object()) {
            std::cerr << "JSON has no valid B \n";
            return false;
        }
        auto& Material_B = j["B"];

        if(!j.contains("Behavior") || !j["Behavior"].is_object()) {
            std::cerr << "JSON has no valid A \n";
            return false;
        }
        auto& behavior = j["Behavior"];

        if(!j.contains("SoundId") || !j["SoundId"].is_object()) {
            std::cerr << "JSON has no valid A \n";
            return false;
        }
        auto& soundId = j["SoundId"];

        SoundSet soundSet = {Material_A, Material_B, behavior};
        SoundEffect soundEffect;
        soundEffect.soundId = soundId;

        soundMap.emplace(soundSet, soundEffect);
    }

    return true;
}