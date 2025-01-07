#pragma once
#include "Groups.h"


enum class EntityType {
    UI,
    Object,
    Unit,
    Projectile
};



struct Request {


};

struct SpawnRequest {
    EntityType entityType;
    std::string name; // "player" , "enemy" ...
    float x, y, w, h, sc;
    int hDir, vDir;
    TeamCode teamCode;
    bool hasPosition = true;
    bool hasDirection = false;
    bool hasTransform = true;
    bool hasOwner = false;
    std::size_t ownerId;
};

struct ProjectileRequest : public SpawnRequest {
    int damage;
    float duration;// 필요하다면 데미지, 크기, 지속시간 등 추가
    bool hasDamage = false;
};


