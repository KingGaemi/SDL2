#pragma once
#include "Groups.h"


enum class EntityType {
    UI,
    Object,
    Unit,
    Projectile,
    Props,
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

    bool hasPosition = true;
    bool hasDirection = false;
    bool hasTransform = true;
    bool hasOwner = false;
    bool hasDamage = false;

    std::size_t ownerId;


};

struct ProjectileRequest : public SpawnRequest {

};


