#include "ICollidable.hpp"
#include "CollisionManager.hpp"

void CollisionManager::HandleCollisions() {
	for(auto it = objects.begin(); it != objects.end() ; it++) {
		auto itt=it; itt++;
		while(itt != objects.end()) {
			Contact res = (*it)->Collide(*itt);
			if(res.isContact) {
				(*it)->OnCollision(*itt,res);
				(*itt)->OnCollision(*it,Contact::Reverse(res));
			}
			itt++;
		}
	}
}