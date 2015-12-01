#ifndef CAMERA_SWITCHER_HPP
#define CAMERA_SWITCHER_HPP

#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <vector>
#include "BasicHeader.hpp"
#include "IPhysical.hpp"
#include "SwitchableCamera.hpp"

class CameraSwitcher : public IPhysical {
public:
	virtual void Update(Time_t /*delta_time*/) {
		if(glfwGetKey(window,GLFW_KEY_TAB) == GLFW_PRESS)
			if(glfwGetKey(window,GLFW_KEY_TAB) != GLFW_PRESS) {
				current++;
				current %= cameras.size();
				Camera.CameraPtr = cameras[current];
			}

		if(glfwGetKey(window,GLFW_KEY_X) == GLFW_PRESS) {
			cameras[current]->Angle = std::min(cameraAngleMax,cameras[current]->Angle + cameraAngleStep);
		}

		if(glfwGetKey(window,GLFW_KEY_Z) == GLFW_PRESS) {
			cameras[current]->Angle = std::max(cameraAngleMin,cameras[current]->Angle - cameraAngleStep);
		}
	}

	virtual void RegisterCamera(ICamera* cam) {
		assert(std::find(cameras.begin(),cameras.end(),cam) == cameras.end());
		cameras.push_back(cam);

		if(Camera.CameraPtr == NULL) {
			current = 0;
			Camera.CameraPtr = cameras[current];
		}
	}

	virtual void UnregisterCamera(const ICamera* cam) {
		assert(cameras.size() > 1);
		auto it = std::find(cameras.begin(),cameras.end(),cam);
		assert(it != cameras.end());

		if(it == cameras.begin()+current) {
			current = 0;
			Camera.CameraPtr = cameras[current];
		} else if(it < cameras.begin()+current) {
			current--;
		}

    	cameras.erase(it);
	}

	SwitchableCamera Camera;	

	virtual void SetCollisionPrimitives() {};
	virtual void OnCollision(IPhysical* /*other*/,CollisionInfo /*details*/) {};

	CameraSwitcher()
	: IPhysical(Position_t(0.0)) {}
protected:
	std::vector<ICamera*> cameras;
	unsigned short int current = 0;
	const float cameraAngleStep = 0.01;
	const float cameraAngleMin = 0.1*M_PI;
	const float cameraAngleMax = 0.45*M_PI;
};

#endif