#ifndef ICOLLIDABLE_HPP
#define ICOLLIDABLE_HPP

#include <utility>
#include <list>
#include <glm/glm.hpp>
#include "Contact.hpp"
#include "CollisionPrimitive.hpp"
#include "IPositionable.hpp"

class ICollidable : public virtual IPositionable {
public:
	virtual void SetPrimitives() = 0;
	virtual Contact Collide(const ICollidable* other) const;
	virtual void OnCollision(ICollidable* other,Contact details) = 0;
	virtual ~ICollidable() { Primitives.clear(); }
	std::list<std::pair<CollisionPrimitive,glm::vec3> > Primitives;
};

#endif