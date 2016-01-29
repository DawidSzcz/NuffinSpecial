#ifndef COLLISION_INFO_HPP
#define COLLISION_INFO_HPP

#include "BasicHeader.hpp"

struct CollisionInfo {
	bool isContact;
	Normal_t norm;
	Coord_t penetration;

	static CollisionInfo Reverse(CollisionInfo c) { c.norm = -c.norm; return c; }
	
	CollisionInfo(bool isC,Normal_t n=Normal_t(0.0),Coord_t p=0.0)
	: isContact(isC), norm(n), penetration(p) {}
};

#endif