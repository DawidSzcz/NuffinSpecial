#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/shader.hpp"
#include "Renderer.hpp"
#include "ShaderSwitcher.hpp"

GLFWwindow* window;
const unsigned short int window_w = 800;
const unsigned short int window_h = 600;

GLuint programID;

int main(int argc, char* argv[]) {
	// check parameters number
	if(argc != 2) {
		std::cerr << "Usage: " << argv[0]  << " model_file\n";
		return -1;
	}

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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	ShaderSwitcher ss;
	programID = LoadShaders("PhongVertexShader.glsl","PhongPixelShader.glsl");
	ss.Shaders.push_back(programID);
	programID = LoadShaders("PhongVertexShader.glsl","FogPhongPixelShader.glsl");
	ss.Shaders.push_back(programID);
	programID = LoadShaders("PhongVertexShader.glsl","OutlinesPhongPixelShader.glsl");
	ss.Shaders.push_back(programID);
	programID = LoadShaders("GrayVertexShader.glsl","GrayPixelShader.glsl");
	ss.Shaders.push_back(programID);

	glUseProgram(programID);

	Scene s;
	s.LoadModelFromFile(argv[1]);
	Camera c;
	Renderer r;

	const Time_t logicalStep = 0.01;
	Time_t logicalTime = glfwGetTime();
	Time_t lastPrint = logicalTime;
	int frames = 0;

	do {
		Time_t currentTime = glfwGetTime();
		if(currentTime - lastPrint >= 1.0) {
			std::cerr << 1000.0/(Time_t)frames << " ms/frame\n";
			lastPrint = currentTime;
			frames = 0;
		}
		frames++;

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for( ; logicalTime < currentTime ; logicalTime += logicalStep) {
			c.GetControls(logicalStep);
			ss.GetControls();
		}
		r.Render(s,c);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
	
	glfwTerminate();

	return 0;
}  