#ifndef PHYSICS_MANAGER_HPP
#define PHYSICS_MANAGER_HPP

#include <vector>
#include <algorithm>
#include "BasicHeader.hpp"
#include "CollisionInfo.hpp"
#include "IPhysical.hpp"

class PhysicsManager {
public:
	virtual void RegisterBody(IPhysical* body) {
		assert(std::find(bodies.begin(),bodies.end(),body) == bodies.end());
		bodies.push_back(body);
	}

	virtual void UnregisterBody(IPhysical* body) {
		auto it = std::find(bodies.begin(),bodies.end(),body);
		assert(it != bodies.end());
    	bodies.erase(it);
	}

	virtual void Frame(float delta_time) {
		for(auto body : bodies)
			body->Update(delta_time);
		handleCollisions();
	}

	virtual ~PhysicsManager() {}
protected:
	std::vector<IPhysical*> bodies;

	virtual void handleCollisions() {
	for(auto it = bodies.begin(); it != bodies.end() ; it++) {
		auto itt=it; itt++;
		for( ; itt != bodies.end() ; itt++) {
			CollisionInfo res = (*it)->Collide(*itt);
			if(res.isContact) {
				(*it)->OnCollision(*itt,res);
				(*itt)->OnCollision(*it,CollisionInfo::Reverse(res));
			}
		}
	}
}
};

#endif