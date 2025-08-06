#pragma once

#include "engine/math/Rect.h"
#include "Components/ColliderComponent.h"







class Collision {
public:

	bool static AABB(const Rect& recA , const Rect& recB){
		
		if(	
			recA.x + recA.w >= recB.x &&
			recB.x + recB.w >= recA.x &&
			recA.y + recA.h >= recB.y &&
			recB.y + recB.h >= recA.h)
		{
			return true;
		}

		return false;

	}

	bool static AABB(const ColliderComponent& cA, const ColliderComponent& cB){
	    // 표준 AABB 충돌 체크
	    const Rect& a = cA.collider;
	    const Rect& b = cB.collider;
	    if (a.x < b.x + b.w  &&
	        a.x + a.w > b.x  &&
	        a.y < b.y + b.h  &&
	        a.y + a.h > b.y)
	    {
	        return true;
	    }
	    return false;
	}

	// bool static CCC(const ColliderComponent& c1, const ColliderComponent& c2) {
	//     float dx = static_cast<float>(c1.collider.x - c2.collider.x);
	//     float dy = static_cast<float>(c1.collider.y - c2.collider.y);
	//     float distSq = dx * dx + dy * dy;

	//     float radiusSum = c1.circleCollider.radius + c2.circleCollider.radius;
	//     float radiusSumSq = radiusSum * radiusSum;

	//     return distSq <= radiusSumSq;
	// }

};











