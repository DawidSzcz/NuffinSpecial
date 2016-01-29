#include "BasicHeader.hpp"
#include <glm/gtx/norm.hpp>
#include <glm/gtx/perpendicular.hpp>
#include "CollisionInfo.hpp"
#include "CollisionPrimitive.hpp"

CollisionInfo CollisionPrimitive::CheckIntersection(const CollisionPrimitive& other,Position_t rel_pos) const {
	if(shape == SPHERE && other.shape == SPHERE) {
		if(glm::length2(rel_pos) >= (r+other.r)*(r+other.r))
			return CollisionInfo(false);
		else
			return CollisionInfo(true, -glm::normalize(rel_pos) , r+other.r - glm::length(rel_pos));
	} else if(shape == HALFPLANE && other.shape == SPHERE) {
		Position_t closest = glm::perp(rel_pos,norm);
		Position_t dist = rel_pos - closest;
		bool opposite = (glm::dot(dist,norm) <= 0.0);

		if(!opposite && glm::length2(dist) > other.r*other.r)
			return CollisionInfo(false);
		else {
			if(opposite) return CollisionInfo(true,-norm,other.r + glm::length(dist));
			else return CollisionInfo(true,-norm,other.r - glm::length(dist));
		}
	} else if(shape == SPHERE && other.shape == HALFPLANE)
		return CollisionInfo::Reverse(other.CheckIntersection(*this,-rel_pos));
	else {// HALFPLANE, HALFPLANE
		// assume: not intersecting
		return CollisionInfo(false);
	}	
}	