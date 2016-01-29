#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "BasicHeader.hpp"

class PointLight {
public:
	Position_t Position;
	Colour_t Intensity; // RGB colour * constant e.g. glm::vec3(50.0,50.0,50.0)
	virtual ~PointLight() {}
};

#endif