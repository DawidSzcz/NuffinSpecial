#ifndef SHINY_BUBBLE_HPP
#define SHINY_BUBBLE_HPP

#include "BasicHeader.hpp"
#include "Bubble.hpp"
#include "PointLight.hpp"

class ShinyBubble : public Bubble {
public:
	PointLight Light;

	virtual void Update(Time_t delta_time) {
		// Position += (Coord_t)delta_time * Velocity;
		// Radius += 0.01 * Initial_radius * delta_time * glm::length(Velocity);
		// updateCollisionPrimitives();
		// updateModelMatrix();
		Bubble::Update(delta_time);
		updateLightPosition();
	}

	virtual void OnCollision(IPhysical* other,CollisionInfo details) {
		assert(details.isContact);

		if(dynamic_cast<Player*>(other) != NULL) {
			NotifyObservers(Notification::SHINY_BUBBLE_HIT);
		} else if(dynamic_cast<TopBorder*>(other) != NULL) {
			Position.y = 0.0;
			Radius = Initial_radius;
			updateCollisionPrimitives();
			updateModelMatrix();
			updateLightPosition();
		}
	}

	ShinyBubble(Position_t pos,Coord_t r,Position_t vel,Colour_t c)
	: Bubble(pos,r,vel,c) {
		Light.Intensity = 25.0f * c;
		updateLightPosition();
	}
protected:
	virtual void updateLightPosition() {
		Light.Position = Position;
	}
};

#endif