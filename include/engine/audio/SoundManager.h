#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"


struct SoundEffect {
    std::string soundId; // 또는 Mix_Chunk* (SDL2_mixer용)
    int volume = 100;
};

struct SoundSet{
    std::string material_A;
    std::string material_B;
    std::string behavior;
     // 비교 연산자 (unordered_map에서 키 비교를 위해 필요)
    bool operator==(const SoundSet& other) const {
        return (material_A == other.material_A && material_B == other.material_B && behavior == other.behavior) ||
               (material_A == other.material_B && material_B == other.material_A && behavior == other.behavior);
    }
};


// SoundSet을 위한 해시 함수 정의
struct SoundSetHash {
    std::size_t operator()(const SoundSet& s) const {
        // std::hash를 이용해 각 문자열을 해시하고 XOR 연산으로 합침
        std::hash<std::string> hasher;
        std::size_t h1 = hasher(s.material_A);
        std::size_t h2 = hasher(s.material_B);
        std::size_t h3 = hasher(s.behavior);
        
        // A-B, B-A 순서 무관하게 만들기 위해 std::min, std::max 사용
        return h1 ^ h2 ^ h3;
    }
};


class SoundManager{

public:

	bool loadMusic(const std::string& musicID, std::string_view p_filePath);
	bool loadEffect(const std::string& effectID, std::string_view p_filePath);
 	// 배경 음악 재생 (-1 = 무한 반복)
    bool playMusic(const std::string& musicID, int loops = -1);
    // 효과음 재생 (채널 -1 = 사용 가능한 첫 번째 채널, 0 = 반복 없음)
    bool playEffect(const std::string& effectID, int loops = 0);
    bool playABSound(const std::string& MatA, const std::string& MatB, const std::string& behavior);

    void setEffectVolume(int volume) {
        Mix_Volume(-1, volume);
    }


    bool registerEffects();	

	void cleanup(){
		for (auto& pair : effects) {
            Mix_FreeChunk(pair.second);
        }
		for (auto& pair : musics) {
            Mix_FreeMusic(pair.second);
        }
        musics.clear();
        effects.clear();
	    Mix_CloseAudio();
	}


    // 배경 음악 재생 (-1 = 무한 반복)
    // Mix_PlayMusic(music, -1);

    // // 효과음 재생 (채널 -1 = 사용 가능한 첫 번째 채널, 0 = 반복 없음)
    // Mix_PlayChannel(-1, effect, 0);


private:
	std::unordered_map<std::string, Mix_Music*> musics;
	std::unordered_map<std::string, Mix_Chunk*> effects;
    std::unordered_map<SoundSet, SoundEffect, SoundSetHash> soundMap;
};