#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <GLFW/glfw3.h>
extern GLFWwindow* window;
extern GLuint programID;

void Camera::GetControls(Time_t delta_time) {
	updateMoveSpeed();
	updateDirection(delta_time);
	updatePosition(delta_time);
	updateAngle();
}

void Camera::Bind() const {
	glm::mat4 Projection = glm::perspective(angle, 4.0f / 3.0f, 0.01f, 100000.0f);
	glm::mat4 View       = glm::lookAt(position,position+getDirectionVector(),upVector);
	glm::mat4 Model = glm::mat4(1.0);
	glm::mat4 MV = View * Model;
	glm::mat4 NormalMatrix = glm::inverseTranspose(MV);
	glm::mat4 MVP = Projection * MV;


	GLuint MID = glGetUniformLocation(programID,"M");
	GLuint VID = glGetUniformLocation(programID,"V");
	GLuint MVPID = glGetUniformLocation(programID,"MVP");
	GLuint NormalMatrixID = glGetUniformLocation(programID,"NormalMatrix");
	glUniformMatrix4fv(VID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(MID, 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(NormalMatrixID, 1, GL_FALSE, &NormalMatrix[0][0]);

}

void Camera::updateDirection(Time_t delta_time) {
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window,initial_mouse_x,initial_mouse_y);

	Coord_t angle_x = ((double)initial_mouse_x - xpos) * delta_time * rotatingSpeed;
	Coord_t angle_y = ((double)initial_mouse_y - ypos) * delta_time * rotatingSpeed;

	glm::vec4 tmp = glm::rotate(Matrix_t(1.0),angle_x,upVector) * glm::vec4(rightVector,0.0);
	rightVector.x = tmp.x;
	rightVector.y = tmp.y;
	rightVector.z = tmp.z;
	tmp = glm::rotate(Matrix_t(1.0),angle_y,rightVector) * glm::vec4(upVector,0.0);
	upVector.x = tmp.x;
	upVector.y = tmp.y;
	upVector.z = tmp.z;
	assert(glm::length(rightVector) >= 1 - eps && glm::length(rightVector) <= 1 + eps);
	assert(glm::length(upVector) >= 1 - eps && glm::length(upVector) <= 1 + eps);
	assert(glm::length(getDirectionVector()) >= 1 - eps && glm::length(getDirectionVector()) <= 1 + eps);
	assert(glm::dot(rightVector,upVector) >= - eps && glm::dot(rightVector,upVector) <= eps);
}

void Camera::updatePosition(Time_t delta_time) {
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += (Coord_t)delta_time * moveSpeed * getDirectionVector();
	}
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= (Coord_t)delta_time * moveSpeed * getDirectionVector();
	}
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += (Coord_t)delta_time * moveSpeed * rightVector;
	}
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= (Coord_t)delta_time * moveSpeed * rightVector;
	}
	if (glfwGetKey( window, GLFW_KEY_PAGE_UP ) == GLFW_PRESS){
		position += (Coord_t)delta_time * moveSpeed * upVector;
	}
	if (glfwGetKey( window, GLFW_KEY_PAGE_DOWN ) == GLFW_PRESS){
		position -= (Coord_t)delta_time * moveSpeed * upVector;
	}
}

void Camera::updateAngle() {
	if(glfwGetKey(window,GLFW_KEY_X) == GLFW_PRESS) {
		angle = glm::min(cameraAngleMax,angle + cameraAngleStep);
	}

	if(glfwGetKey(window,GLFW_KEY_Z) == GLFW_PRESS) {
		angle = glm::max(cameraAngleMin,angle - cameraAngleStep);
	}
}

void Camera::updateMoveSpeed() {
	if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
		moveSpeed *= 1.0 + moveSpeedStep;
	}

	if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
		moveSpeed = glm::max(moveSpeedMin,(Coord_t)(moveSpeed * (1.0-moveSpeedStep)));
	}
}