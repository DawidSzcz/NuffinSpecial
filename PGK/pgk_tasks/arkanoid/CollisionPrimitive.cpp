#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/perpendicular.hpp>
#include "CollisionPrimitive.hpp"

Contact CollisionPrimitive::CheckIntersection(CollisionPrimitive other,glm::vec3 rel_pos) const {
	if(shape == CIRCLE && other.shape == CIRCLE) {
		if(glm::length2(rel_pos) >= (r+other.r)*(r+other.r))
			return Contact(false);
		else
			return Contact(true, -glm::normalize(rel_pos) , r+other.r - glm::length(rel_pos));
	} else if(shape == HALFPLANE && other.shape == CIRCLE) {
		glm::vec2 n = glm::vec2(norm[0],norm[1]);
		glm::vec2 pos = glm::vec2(rel_pos[0],rel_pos[1]);
		glm::vec2 closest = glm::perp(pos,n);
		glm::vec2 dist = pos - closest;
		bool opposite = (glm::dot(dist,n) <= 0.0);

		if(!opposite && glm::length2(dist) > other.r*other.r)
			return Contact(false);
		else {
			if(opposite) return Contact(true,-norm,other.r + glm::length(dist));
			else return Contact(true,-norm,other.r - glm::length(dist));
		}
	} else if(shape == CIRCLE && other.shape == HALFPLANE)
		return Contact::Reverse(other.CheckIntersection(*this,-rel_pos));
	else {// HALFPLANE, HALFPLANE
		// assume: not intersecting
		return Contact(false);
	}
}