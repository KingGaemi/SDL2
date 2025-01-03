#pragma once

#include "Rect.h"
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

};











