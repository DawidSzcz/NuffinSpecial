#ifndef TARGET_BORDER_HPP
#define TARGET_BORDER_HPP

#include "BasicHeader.hpp"
#include "Border.hpp"
#include "IObservable.hpp"

class TargetBorder : public Border, public IObservable {
public:
	virtual void OnCollision(IPhysical* other,CollisionInfo details) {
		assert(details.isContact);

		if(dynamic_cast<Player*>(other) != NULL) {
			NotifyObservers(Notification::TARGET_HIT);
		} else
			other->Position -= details.penetration * details.norm;
	};

	TargetBorder(Transformation_t modelMatrix,Coord_t width,Coord_t height,Colour_t c)
	: Border(modelMatrix,width,height,c) {}
};

#endif