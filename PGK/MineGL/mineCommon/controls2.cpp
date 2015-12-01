// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;

#include "controls2.hpp"

#define PI 3.14159265

double xpos = 0, ypos = 0, scl = 1, speed = 0.03, zoom = 1.01;
GLfloat xAngle = 0.0, yAngle = 0.0;
bool released = true, is3D = false;

glm::mat4 getCameraPos()
{
	glm::mat4 trans;
	trans = glm::rotate(trans, yAngle, glm::vec3(1.0, 0.0, 0.0));
	trans = glm::rotate(trans, xAngle, glm::vec3(0.0, 1.0, 0.0));
	trans = glm::translate(trans, glm::vec3(xpos, ypos, 0.0f));
 	return glm::scale(trans, glm::vec3(scl, scl, 1)); 
	//return trans;
}
glm::vec2 getAngles()
{
	return glm::vec2(xAngle, yAngle);
}


bool is3d()
{
	return is3D;
}

// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float mouseSpeed = 0.005f;


void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_KP_SUBTRACT  ) == GLFW_PRESS){
		scl /= zoom;
		xpos/= zoom;
		ypos /= zoom;
	}
	if (glfwGetKey( window, GLFW_KEY_KP_ADD    ) == GLFW_PRESS){
		scl *= zoom;
		xpos *= zoom;
		ypos *= zoom;
		std::cout<<"ZOOM: " << xpos << " " << ypos << std::endl;
	}
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		if(!is3D)	
			ypos -= speed;
		else
			yAngle < 45.0 ? yAngle += speed*5 : yAngle = 45.0;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		if(!is3D)	
			ypos += speed;
		else
			yAngle > -45.0 ? yAngle -= speed*5 : yAngle = -45.0;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		if(!is3D)	
			xpos -= speed;
		else
			xAngle < 45.0 ? xAngle += speed*5 : xAngle = 45.0;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		if(!is3D)	
			xpos += speed;
		else
			xAngle > -45.0 ? xAngle -= speed*5 : xAngle = -45.0;
	}
	if (released && glfwGetKey( window, GLFW_KEY_TAB) == GLFW_PRESS){
		std::cout<<"Rot: " << is3D << std::endl;
		is3D = !is3D;
		released = false;
	} 
	if (glfwGetKey( window, GLFW_KEY_TAB) == GLFW_RELEASE){
		released = true;
	}
	lastTime = currentTime;
}
