#ifndef COLLISION_PRIMITIVE_HPP
#define COLLISION_PRIMITIVE_HPP

#include <glm/glm.hpp>
#include "Contact.hpp"

class CollisionPrimitive {
public:
	enum Shape {
		CIRCLE,
		HALFPLANE
	} shape;
	GLfloat r;
	glm::vec3 norm;

	CollisionPrimitive(Shape primitive_shape)
	: shape(primitive_shape), r(0.0), norm(0.0) {}
	Contact CheckIntersection(CollisionPrimitive other,glm::vec3 rel_pos) const;
};

#endif