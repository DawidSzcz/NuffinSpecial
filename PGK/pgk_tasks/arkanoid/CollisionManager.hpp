#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include <list>
#include "ICollidable.hpp"

class CollisionManager {
public:
	virtual void Register(ICollidable* x) { if(x != NULL) objects.push_back(x); }
	virtual void HandleCollisions();
	~CollisionManager() { objects.clear(); }
protected:
	std::list<ICollidable*> objects;
};

#endif