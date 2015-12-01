#ifndef ICAMERA_HPP
#define ICAMERA_HPP

#include "BasicHeader.hpp"

class ICamera {
public:
	Position_t Position;
	Position_t Direction;
	Position_t UpVector;
	float Angle = 0.3*M_PI;

	virtual Transformation_t GetView() const = 0;
	virtual Transformation_t GetProjection() const = 0;
	virtual ~ICamera() {}
};

#endif