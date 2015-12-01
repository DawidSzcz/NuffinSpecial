#include <glm/glm.hpp>
#include "Contact.hpp"
#include "CollisionPrimitive.hpp"
#include "ICollidable.hpp"

Contact ICollidable::Collide(const ICollidable* other) const {
	glm::vec3 rel_pos = other->Position - Position;

	for(auto it = Primitives.begin() ; it != Primitives.end() ; it++) {
		auto p1 = it->first;
		glm::vec3 aux = rel_pos - it->second;

		for(auto it2 = other->Primitives.begin() ; it2 != other->Primitives.end() ; it2++) {
			auto p2 = it2->first;

			Contact res = p1.CheckIntersection(p2,aux + it2->second);
			if(res.isContact) return res;
		}
	}

	return Contact(false);
}