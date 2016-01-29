#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Card.hpp"
#include "CardsDeck.hpp"
#include "Game.hpp"
#include "common/shader.hpp"
#include "common/text2D.hpp"
using namespace std;
using namespace glm;

// shaders
const char* const vshader = "SimpleVertexShader.vertexshader";
const char* const fshader = "ColorFragmentShader.fragmentshader";

// constants
const char* const font_dds_file = "Holstein.DDS";
const char* const window_title = "Memory: The Game";
const int window_scale = 100;

const int cards_n = 4*4;
const int cards_to_draw_n = 4*4 + 2;
const int vs_per_card = 6;

// a single card in the middle
static const GLfloat card_vertices[vs_per_card*3] = { 
	-0.2f, -0.2f, 0.0f,
	-0.2f,  0.2f, 0.0f,
	 0.2f, -0.2f, 0.0f,
	-0.2f,  0.2f, 0.0f,
	 0.2f, -0.2f, 0.0f,
	 0.2f,  0.2f, 0.0f,
};

// offsets for placing 16 cards uniformly distributed on the screen
static const GLfloat offset[cards_n*3] {
	-0.75f,  0.75f, 0.0f,
	-0.25f,  0.75f, 0.0f,
	 0.25f,  0.75f, 0.0f,
	 0.75f,  0.75f, 0.0f,
	-0.75f,  0.25f, 0.0f,
	-0.25f,  0.25f, 0.0f,
	 0.25f,  0.25f, 0.0f,
	 0.75f,  0.25f, 0.0f,
	-0.75f, -0.25f, 0.0f,
	-0.25f, -0.25f, 0.0f,
	 0.25f, -0.25f, 0.0f,
	 0.75f, -0.25f, 0.0f,
	-0.75f, -0.75f, 0.0f,
	-0.25f, -0.75f, 0.0f,
	 0.25f, -0.75f, 0.0f,
	 0.75f, -0.75f, 0.0f,
};

// cards backs color
static const GLfloat back_color[3] = { 0.9f, 0.8f, 0.6f, };
	
static const GLfloat face_colors[(cards_n/2)*3] {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	0.8f, 0.4f, 0.3f,
};

GLFWwindow* window;
CardsDeck cards(4,4);
Game game(&cards);
	
void key_callback(GLFWwindow* /*w*/,int key,int /*scancode*/,int action,int /*mods*/) {
	game.ProcessKeyAction(key,action);
}


int main( void )
{
	// Initialise GLFW
	if( !glfwInit() ) {
		cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 5*window_scale, 7*window_scale, window_title, NULL, NULL);
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
	glfwSetKeyCallback(window,key_callback);

	// Dark green background
	glClearColor(0.02f,0.5f,0.25f,0.0f);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders(vshader,fshader);

	// Get a handle for our buffers
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	static GLfloat g_vertex_buffer_data[cards_to_draw_n*vs_per_card*3];
	
	GLuint vertexColorID = glGetAttribLocation(programID, "vertexColor");
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	static GLfloat g_color_buffer_data[cards_to_draw_n*vs_per_card*3];
	
	initText2D(font_dds_file);

	// init game logic
	auto deck = cards.GetDeck(); int curr = 0;
	assert(deck.size() == cards_n);
	for(auto it=deck.begin() ; it < deck.end() ; it++) {
		Card* card = *it;
		
		copy(face_colors+(curr/2)*3,face_colors+(curr/2)*3+3,card->FaceColor);
		curr++;
	}

	cards.Shuffle();

	deck = cards.GetDeck(); curr=0;
	for(auto it=deck.begin() ; it < deck.end() ; it++) {
		Card* card = *it;
		
		copy(back_color,back_color+3,card->BackColor);

		assert(card->VerticesNum == vs_per_card);
		for(int i=0 ; i < card->VerticesNum ; i++)
			for(int j=0 ; j < 3 ; j++) {
				card->Coords[i*3 + j] = card_vertices[i*3+j] + offset[curr*3 + j];
			}

		curr++;
	}
	
	double lastTime = glfwGetTime();
	do {
		// Measure time between frames
		double currentTime = glfwGetTime();
		double delta = currentTime - lastTime;
		lastTime = currentTime;
		
		// generate drawable data 
		GLfloat* vbend = g_vertex_buffer_data;
		GLfloat* cbend = g_color_buffer_data;
		game.GenerateBufferData(&vbend,&cbend);

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		glVertexAttribPointer(
			vertexPosition_modelspaceID, // The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(vertexColorID);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
		glVertexAttribPointer(
			vertexColorID,               // The attribute we want to configure
			3,                           // size
			GL_FLOAT,                    // type
			GL_FALSE,                    // normalized?
			0,                           // stride
			(void*)0                     // array buffer offset
		);

		// Draw triangles
		glDrawArrays(GL_TRIANGLES, 0, (vbend - g_vertex_buffer_data)/3);

		glDisableVertexAttribArray(vertexPosition_modelspaceID);
		glDisableVertexAttribArray(vertexColorID);
		
		// game logic
		game.ProcessFrame(delta);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );


	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);

	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}