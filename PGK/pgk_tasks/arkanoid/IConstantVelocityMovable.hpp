#ifndef ICONSTANT_VELOCITY_MOVABLE_HPP
#define ICONSTANT_VELOCITY_MOVABLE_HPP

#include <glm/glm.hpp>
#include "IMovable.hpp"

class IConstantVelocityMovable : public IMovable {
public:
	IConstantVelocityMovable(glm::vec3 position=glm::vec3(0.0),glm::vec3 velocity=glm::vec3(0.0))
	: IMovable(position), Velocity(velocity) {}
	virtual void UpdateState(double delta_sec) { Position += (float)delta_sec*Velocity; }
	glm::vec3 Velocity;
};

#endif