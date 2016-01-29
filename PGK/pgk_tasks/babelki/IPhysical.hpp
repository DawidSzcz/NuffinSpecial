#ifndef IPHYSICAL_HPP
#define IPHYSICAL_HPP

#include <vector>
#include <utility>
#include "BasicHeader.hpp"
#include "CollisionPrimitive.hpp"

class IPhysical {
public:
	Position_t Position;
	
	virtual void Update(Time_t delta_time) = 0;
	virtual void SetCollisionPrimitives() = 0;
	virtual void OnCollision(IPhysical* other,CollisionInfo details) = 0;
	
	virtual CollisionInfo Collide(const IPhysical* other) const {
		Position_t rel_pos = other->Position - Position;

		for(auto pair : CollisionPrimitives) {
			CollisionPrimitive prim = pair.first;
			Position_t aux = rel_pos - pair.second;

			for(auto pair2 : other->CollisionPrimitives) {
				CollisionInfo res = prim.CheckIntersection(pair2.first,aux + pair2.second);
				if(res.isContact) return res;
			}
		}

		return CollisionInfo(false);
	}

	std::vector<std::pair<CollisionPrimitive,Position_t> > CollisionPrimitives;

	IPhysical(Position_t pos)
	: Position(pos) {}

	virtual ~IPhysical() {}
};

#endif