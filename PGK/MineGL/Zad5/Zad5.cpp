#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <array>
#include <string.h>
#include <iostream>
#include <fstream>
#include "shader.hpp"

GLFWwindow* window;
int windowWidth = 1024, windowHeight = 1024;

int makeWindow(int x, int y, char* str)
{        
	if( !glfwInit() )
        {
                fprintf( stderr, "Failed to initialize GLFW\n" );
                return -1;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow( x, y, str, NULL, NULL);
        if( window == NULL ){
                fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
                glfwTerminate();
                return -1;
        }
        glfwMakeContextCurrent(window);
        // Initialize GLEW
        glewExperimental = true; // Needed for core profile
        if (glewInit() != GLEW_OK) {
                fprintf(stderr, "Failed to initialize GLEW\n");
                return -1;
        }

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        // Dark blue background
        glClearColor(0.0f, 0.5f, 0.4f, 0.0f);
}

int main(int argc, char * argv[] )
{	
	glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
	if(makeWindow(windowWidth, windowHeight, (char*)"Zad3") == -1)
		return -1;
		

 	GLuint programID1 = LoadShaders( "shader.vertexshader", "shader.shader" );
	GLfloat vertexes[] = {
    		-1.0f, 1.0f, 0.0f, 
     		1.0f, 1.0f, 0.0f, 
     		-1.0f, -1.0f, 0.0f, 
		1.0f, -1.0f, 0.0f, 
	};  
	GLuint indices[] = {  2, 0, 1, 2, 3, 1};
        
	GLuint VAO, VBA, EBO;
	
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
	glGenBuffers(1, &VBA);
    glBindBuffer(GL_ARRAY_BUFFER,VBA);
	glBufferData(GL_ARRAY_BUFFER, 12* sizeof(GLfloat), vertexes, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
	glVertexAttribPointer(
                    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    3*sizeof(GLfloat),                  // stride
                    (void*)0            // array buffer offset
        );
	glEnableVertexAttribArray(0);
	
	//glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		
		glUseProgram(programID1);	
		
		glBindVertexArray(VAO);		
        	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}
