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
    float rotation;

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
    float x, y, sc, rot;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    int w, h;

    Rect srcRect;
    FRect dstRect;

};

struct ProjectileRequest : public SpawnRequest {

};


