#pragma once
#include "engine/ecs/core/Component.h"



enum class Material{
	Grass,
	Rock,
	Water,
	Leather,
	Flesh,
	None
};

enum class SoundBehavior{
	Walk,
	Run,
	Swing,
	Cast,
	Hit,
	None
};



// struct SoundSet {
// 	Material factorA;
// 	Material factorB;
// 	SoundBehavior soundBehavior;
// };

class SoundEffectComponent : public Component {
public:
	SoundEffectComponent(std::string bodyMaterial, std::string footMaterial,std::string typeMaterial) : bodyMaterial(bodyMaterial), footMaterial(footMaterial), typeMaterial(typeMaterial) {}

	std::string bodyMaterial;
	std::string footMaterial;
	std::string typeMaterial;
};