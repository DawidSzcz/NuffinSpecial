#include "ShaderSwitcher.hpp"

#include <GLFW/glfw3.h>
extern GLFWwindow* window;
extern GLuint programID;

void ShaderSwitcher::GetControls() {
	assert(Shaders.size() > 0);

	if(glfwGetKey(window,GLFW_KEY_TAB) == GLFW_PRESS)
		if(glfwGetKey(window,GLFW_KEY_TAB) != GLFW_PRESS) {
			current = (current+1) % Shaders.size();
			programID = Shaders[current];
			glUseProgram(programID);
		}
}