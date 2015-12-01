#ifndef IMOVABLE_HPP
#define IMOVABLE_HPP

#include <glm/glm.hpp>
#include "IPositionable.hpp"

class IMovable : public virtual IPositionable {
public:
	IMovable(glm::vec3 position=glm::vec3(0.0))
	: IPositionable(position) {}
	virtual void UpdateState(double delta_sec)=0;
};

#endif