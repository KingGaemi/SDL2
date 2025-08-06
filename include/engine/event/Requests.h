#pragma once
#include <string>
#include "engine/math/Rect.h"



enum class EntityType {
    UI,
    Object,
    Unit,
    Projectile,
    Props,
    Wall,
    Camera,
    Image,
    Effect,
    Item,
    Text,
    Manager
};



struct Request {


};

struct SpawnRequest {
    EntityType entityType;
    std::string name; // "player" , "enemy" ...
    float x, y, w, h, sc;
    int hDir, vDir;
    int teamCode;  // 0 = ally, 1 = enemy, 2 = neutral

    // if it's projectile..
    int damage;
    float projectileSpeed, projectileScale;
    float duration;
    float rotation = 0.0f;

    bool hasPosition = true;
    bool hasDirection = false;
    bool hasTransform = false;
    bool hasOwner = false;
    bool hasDamage = false;
    bool hasVelocity = false;

    std::size_t ownerId;


};

struct EffectRequest {
    std::string textureId;
    float rot = 0.0f;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float opacity = 1.0f;
    int zIndex = 1;
    int textNumber = 0;

    Rect srcRect;
    FRect dstRect;

};

struct ProjectileRequest : public SpawnRequest {

};


