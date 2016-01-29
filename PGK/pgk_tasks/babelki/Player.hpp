#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GLFW/glfw3.h>
extern GLFWwindow* window;
extern const unsigned short int window_w,window_h;

#include "BasicHeader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "IPhysical.hpp"
#include "Camera.hpp"
#include "MonochromaticSphere.hpp"
#include "PointLight.hpp"

class Player : public IPhysical {
public:
	Coord_t Radius = 0.1;
	MonochromaticSphere Drawable = MonochromaticSphere(Colour_t(0.0,0.75,0.0));
	Camera FPCamera;
	PointLight Light;

	Position_t UpVector = Position_t(0.0,1.0,0.0);
	Position_t RightVector = Position_t(1.0,0.0,0.0);
	virtual const Position_t GetDirectionVector() { return glm::cross(UpVector,RightVector); };
	Coord_t RotatingSpeed = 0.5;
	Coord_t MoveSpeed = 6.0;

	virtual void Update(Time_t delta_time) {
		updateDirection(delta_time);
		updatePosition(delta_time);
		updateCamera();
		updateModelMatrix();
		updateLightPosition();
	}

	virtual void SetCollisionPrimitives() {
		CollisionPrimitive prim(CollisionPrimitive::SPHERE);
		prim.r = Radius;
		CollisionPrimitives.push_back(std::make_pair(prim,Position_t(0.0)));
	}
	
	virtual void OnCollision(IPhysical* /*other*/,CollisionInfo /*details*/) {}

	Player(Position_t pos)
	: IPhysical(pos) {
		glfwSetCursorPos(window,initial_mouse_x,initial_mouse_y);
		Light.Intensity = Colour_t(2.0,25.0,2.0);
		updateCamera();
		updateModelMatrix();
		SetCollisionPrimitives();
	}

	virtual ~Player() {}
protected:
	const unsigned short int initial_mouse_x = window_w/2;
	const unsigned short int initial_mouse_y = window_h/2;

	virtual void updateDirection(Time_t delta_time) {
		// Get mouse position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		// Reset mouse position for next frame
		glfwSetCursorPos(window,initial_mouse_x,initial_mouse_y);

		Coord_t angle_x = ((double)initial_mouse_x - xpos) * delta_time * RotatingSpeed;
		Coord_t angle_y = ((double)initial_mouse_y - ypos) * delta_time * RotatingSpeed;

		glm::vec4 tmp = glm::rotate(Transformation_t(1.0),angle_x,UpVector) * glm::vec4(RightVector,0.0);
		RightVector.x = tmp.x;
		RightVector.y = tmp.y;
		RightVector.z = tmp.z;
		tmp = glm::rotate(Transformation_t(1.0),angle_y,RightVector) * glm::vec4(UpVector,0.0);
		UpVector.x = tmp.x;
		UpVector.y = tmp.y;
		UpVector.z = tmp.z;
		assert(glm::length(RightVector) >= 1 - eps && glm::length(RightVector) <= 1 + eps);
		assert(glm::length(UpVector) >= 1 - eps && glm::length(UpVector) <= 1 + eps);
		assert(glm::length(GetDirectionVector()) >= 1 - eps && glm::length(GetDirectionVector()) <= 1 + eps);
		assert(glm::dot(RightVector,UpVector) >= - eps && glm::dot(RightVector,UpVector) <= eps);
	}

	virtual void updatePosition(Time_t delta_time) {
		if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
			Position += (Coord_t)delta_time * MoveSpeed * GetDirectionVector();
		}
		if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
			Position -= (Coord_t)delta_time * MoveSpeed * GetDirectionVector();
		}
		if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
			Position += (Coord_t)delta_time * MoveSpeed * RightVector;
		}
		if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
			Position -= (Coord_t)delta_time * MoveSpeed * RightVector;
		}
		if (glfwGetKey( window, GLFW_KEY_PAGE_UP ) == GLFW_PRESS){
			Position += (Coord_t)delta_time * MoveSpeed * UpVector;
		}
		if (glfwGetKey( window, GLFW_KEY_PAGE_DOWN ) == GLFW_PRESS){
			Position -= (Coord_t)delta_time * MoveSpeed * UpVector;
		}
	}

	virtual void updateCamera() {
		FPCamera.Position = Position;
		FPCamera.Direction = GetDirectionVector();
		FPCamera.UpVector = UpVector;
	}

	virtual void updateModelMatrix() {
		Drawable.Model = glm::translate(Transformation_t(1.0),Position);
	}

	virtual void updateLightPosition() {
		Light.Position = Position;
	}
};

#endif