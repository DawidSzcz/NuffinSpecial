// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"


GLfloat x = 0.0, y = 0.0, z = 1.0;

glm::vec3 getCameraPos(){
	return vec3(x, y, z);
}


float speed = 1.0f; // 3 units / second
float mouseSpeed = 0.005f;



void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	
	
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		y -= deltaTime * speed/z;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		y+= deltaTime * speed/z;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		x -= deltaTime * speed/z;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		x += deltaTime * speed/z;
	}
	if (glfwGetKey( window, GLFW_KEY_R  ) == GLFW_PRESS){
		x = 0.0;
		y = 0.0;
		z = 1.0;
	}
	if (glfwGetKey( window, GLFW_KEY_KP_SUBTRACT  ) == GLFW_PRESS){
		z /= (1.0+deltaTime * speed);
	}
	if (glfwGetKey( window, GLFW_KEY_KP_ADD  ) == GLFW_PRESS){
		z *= (1.0+deltaTime * speed);
	}
	
	lastTime = currentTime;
}
