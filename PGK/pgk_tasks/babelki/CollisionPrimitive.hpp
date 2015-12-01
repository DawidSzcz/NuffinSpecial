#ifndef COLLISION_PRIMITIVE_HPP
#define COLLISION_PRIMITIVE_HPP

#include "BasicHeader.hpp"
#include "CollisionInfo.hpp"

class CollisionPrimitive {
public:
	enum Shape {
		SPHERE,
		HALFPLANE
	} shape;
	Coord_t r;
	Normal_t norm;

	CollisionPrimitive(Shape primitive_shape)
	: shape(primitive_shape), r(0.0), norm(0.0) {}
	
	CollisionInfo CheckIntersection(const CollisionPrimitive& other,Position_t rel_pos) const;
};

#endif