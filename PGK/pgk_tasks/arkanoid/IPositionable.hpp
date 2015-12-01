#ifndef IPOSITIONABLE_HPP
#define IPOSITIONABLE_HPP

#include <glm/glm.hpp>

class IPositionable {
public:
	IPositionable(glm::vec3 position=glm::vec3(0.0))
	: Position(position) {}
	glm::vec3 Position;
	virtual ~IPositionable() {}
};

#endif