#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.hpp"

GLFWwindow* window;
const unsigned short int window_w = 800;
const unsigned short int window_h = 600;

int main() {
	// Initialise GLFW
	if( !glfwInit() ) {
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(window_w,window_h, "Mordercze Babelki", NULL, NULL);
	if( window == NULL ) {
		std::cerr << "Failed to open GLFW window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	Game game;
	game.Setup();
	
	do {
		game.Loop();
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
	
	glfwTerminate();

	return 0;
}  