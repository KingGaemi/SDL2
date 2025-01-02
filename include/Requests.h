#pragma once
#include "Groups.h"

struct SpawnRequest {

    std::string type; // "player" , "enemy" ...
    float x, y, w, h, sc;
    int directionX;
    int directionY;
    TeamCode teamCode;
    

};



struct AttackRequest {
    std::string type;  // 예: "slash"
    float x, y;
    int hDir;
    int vDir;
    int damage;
    int scale;
    float duration;// 필요하다면 데미지, 크기, 지속시간 등 추가
    TeamCode teamCode;

};


