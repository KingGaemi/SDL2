#include "Collision.h"
#include <iostream>



bool Collision::AABB(const Rect& recA , const Rect& recB){
		
		if(	recA.x + recA.w >= recB.x &&
			recB.x + recB.w >= recA.x &&
			recA.y + recA.h >= recB.y &&
			recB.y + recB.h >= recA.h)
		{
			return true;
		}

		return false;

}



bool Collision::AABB(const ColliderComponent& colA , const ColliderComponent& colB ){

	if(AABB(colA.collider, colB.collider)){
		std::cout << colA.tag << " Hits " << colB.tag << std::endl;

		return true;

	}

	return false;
}

