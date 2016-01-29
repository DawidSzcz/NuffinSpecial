#ifndef SWITCHABLE_CAMERA_HPP
#define SWITCHABLE_CAMERA_HPP

#include "BasicHeader.hpp"
#include "ICamera.hpp"

class SwitchableCamera : public ICamera {
public:
	const ICamera* CameraPtr = NULL;

	virtual Transformation_t GetView() const {
		assert(CameraPtr != NULL);
		return CameraPtr->GetView();
	}

	virtual Transformation_t GetProjection() const {
		assert(CameraPtr != NULL);
		return CameraPtr->GetProjection();
	}
};

#endif