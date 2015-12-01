#ifndef FPCAMERA_HPP
#define FPCAMERA_HPP

#include "BasicHeader.hpp"
#include "ICamera.hpp"

class Camera : public ICamera {
public:
	Transformation_t GetView() const { return glm::lookAt(Position,Position+Direction,UpVector); }
	Transformation_t GetProjection() const { return glm::perspective(Angle, 4.0f / 3.0f, 0.01f, 300.0f); }
};  

#endif