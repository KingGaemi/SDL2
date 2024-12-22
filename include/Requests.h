#pragma once

struct SpawnRequest {

    std::string type; // "player" , "enemy" ...
    float x, y;
    int directionX;
    int directionY;
    

};



struct AttackRequest {
    std::string type;  // 예: "slash"
    float x, y;
    int directionX;
    int directionY;
    int damage;
    int scale;
    float duration;// 필요하다면 데미지, 크기, 지속시간 등 추가
};


