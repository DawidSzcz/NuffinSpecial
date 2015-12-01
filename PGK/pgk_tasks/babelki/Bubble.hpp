#ifndef BUBBLE_HPP
#define BUBBLE_HPP

#include <utility>
#include <vector>
#include "BasicHeader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "CollisionPrimitive.hpp"
#include "IPhysical.hpp"
#include "MonochromaticSphere.hpp"
#include "Player.hpp"
#include "IObservable.hpp"
#include "TopBorder.hpp"

#include <GLFW/glfw3.h>
extern GLFWwindow* window;

class Bubble : public IPhysical, public IObservable {
public:
	Coord_t Radius;
	const Coord_t Initial_radius;
	Position_t Velocity;
	MonochromaticSphere Drawable;

	virtual void Update(Time_t delta_time) {
		Position += (Coord_t)delta_time * Velocity;
		Radius += 0.01 * Initial_radius * delta_time * glm::length(Velocity);
		updateCollisionPrimitives();
		updateModelMatrix();
	}

	virtual void SetCollisionPrimitives() {
		CollisionPrimitive prim(CollisionPrimitive::SPHERE);
		prim.r = Radius;
		CollisionPrimitives.push_back(std::make_pair(prim,Position_t(0.0)));
	}

	virtual void OnCollision(IPhysical* other,CollisionInfo details) {
		assert(details.isContact);

		if(dynamic_cast<Player*>(other) != NULL) {
			NotifyObservers(Notification::BUBBLE_HIT);
		} else if(dynamic_cast<TopBorder*>(other) != NULL) {
			Position.y = 0.0;
			Radius = Initial_radius;
			updateCollisionPrimitives();
			updateModelMatrix();
		}
	}

	Bubble(Position_t pos,Coord_t r,Position_t vel,Colour_t c)
	: IPhysical(pos), Radius(r), Initial_radius(r), Velocity(vel), Drawable(c) {
		SetCollisionPrimitives();
		updateModelMatrix();
	}
protected:
	virtual void updateModelMatrix() {
		Transformation_t translation =  glm::translate(Transformation_t(1.0),Position);
		Drawable.Model = glm::scale(translation,Position_t(Radius,Radius,Radius));
	}

	virtual void updateCollisionPrimitives() {
		assert(CollisionPrimitives.size() > 0);
		CollisionPrimitives[0].first.r = Radius;
	}
};

#endif