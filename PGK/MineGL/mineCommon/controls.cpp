// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix =  glm::lookAt(
				glm::vec3(0,0,2.5), // Camera is at (4,3,3), in World Space
				glm::vec3(0,0,0), // and looks at the origin
				glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
				);
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 ); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float mouseSpeed = 0.005f;

double xpos = 0, ypos = 0, zpos = 2.5, speed = 0.03, zoom = 1.01;

void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_KP_SUBTRACT  ) == GLFW_PRESS){
		zpos *= zoom;
	}
	if (glfwGetKey( window, GLFW_KEY_KP_ADD    ) == GLFW_PRESS){
		zpos = (0 >  zpos /zoom) ? 0 : zpos / zoom;
	}
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		ypos += speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		ypos -= speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		xpos += speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		xpos -= speed;
	}
	ProjectionMatrix = glm::perspective(initialFoV, 4.0f / 3.0f, 0.1f, 100.0f);
	ViewMatrix       = glm::lookAt(
				glm::vec3(xpos,ypos,zpos), // Camera is at (4,3,3), in World Space
				glm::vec3(xpos,ypos,0), // and looks at the origin
				glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
			);

	lastTime = currentTime;
}