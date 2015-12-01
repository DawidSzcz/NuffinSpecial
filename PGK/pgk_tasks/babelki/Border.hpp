#ifndef BORDER_HPP
#define BORDER_HPP

#include <utility>
#include <vector>
#include "BasicHeader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "CollisionPrimitive.hpp"
#include "IPhysical.hpp"
#include "Square.hpp"

class Border : public IPhysical {
public:
	Normal_t Normal;
	Square Drawable;

	virtual void Update(Time_t /*delta_time*/) {}

	virtual void SetCollisionPrimitives() {
		CollisionPrimitive prim(CollisionPrimitive::HALFPLANE);
		prim.norm = Normal;
		CollisionPrimitives.push_back(std::make_pair(prim,Position_t(0.0)));
	}

	virtual void OnCollision(IPhysical* other,CollisionInfo details) {
		assert(details.isContact);

		other->Position -= (details.penetration+0.0001f) * details.norm;
	};

	Border(Transformation_t modelMatrix,Coord_t width,Coord_t height,Colour_t c)
	: IPhysical(Position_t(0.0)), Drawable(width,height,c) {
		glm::vec4 tmp = modelMatrix * glm::vec4(0.0,0.0,0.0,1.0);
		Position.x = tmp.x;
		Position.y = tmp.y;
		Position.z = tmp.z;

		//basic normal is (0,0,1)
		tmp = modelMatrix * glm::vec4(0.0,0.0,1.0,0.0);
		Normal.x = tmp.x;
		Normal.y = tmp.y;
		Normal.z = tmp.z;
		
		Drawable.Model = modelMatrix * Drawable.Model;
		SetCollisionPrimitives();
	}
};

#endif