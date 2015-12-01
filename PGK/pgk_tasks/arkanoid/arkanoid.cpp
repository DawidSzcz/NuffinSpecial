#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.hpp"
using namespace std;

GLFWwindow* window;
const char* const window_title = "Arkanoid: The Game";

int main() {
//*****************************************************************************
//********************** INITIALISE LIBRARIES *********************************

	// Initialise GLFW
	if( !glfwInit() ) {
		cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(720,720, window_title, NULL, NULL);
	if( window == NULL ) {
		cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW\n";
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);

//*****************************************************************************
//******************************** PLAY GAME **********************************
	Game game;
	glfwSetKeyCallback(window,Game::KeyCallback);

	double lastTime = glfwGetTime();
	int frames = 0;
	do {
		// Measure time between frames
		double currentTime = glfwGetTime();
		if(floor(currentTime) > floor(lastTime)) {
			cerr << frames << " FPS\n"; frames = 0;
		}

		double delta = currentTime - lastTime;
		lastTime = currentTime;
		frames++;

		game.HandleFrame(delta);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while(glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}