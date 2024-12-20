#pragma once

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "Components/ColliderComponent.h"





class Collision{	


public:


	bool static AABB(const Rect& recA , const Rect& recB);

	bool static AABB(const ColliderComponent& colA , const ColliderComponent& colB );
	
private:

	

};





