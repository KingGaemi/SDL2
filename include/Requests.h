#pragma once
#include "Groups.h"
#include "Rect.h"



enum class EntityType {
    UI,
    Object,
    Unit,
    Projectile,
    Props,
    Wall,
    Camera,
    Item
};



struct Request {


};

struct SpawnRequest {
    EntityType entityType;
    std::string name; // "player" , "enemy" ...
    float x, y, w, h, sc;
    int hDir, vDir;
    TeamCode teamCode;

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


