// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;
static std::vector < GLfloat > *data;
static int vertexAmount = 0; 
static int size;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shader.hpp"
#include "controls.hpp"

void resize(int args)
{
        GLfloat minC = 10000, maxC = -10000, minX = 10000, maxX = -10000, minY = 10000, maxY = -10000, scaleX, scaleY, scaleC, moveX, moveY;
		for(int arg = 0; arg < args; arg++)
		{
				for(int i = 0; i < data[arg].size();i++)
				{
				        if(data[arg][i] < minX)
				                minX = data[arg][i];
				        if(data[arg][i] > maxX)
				                maxX = data[arg][i];
				        if(data[arg][++i] < minY)
				                minY = data[arg][i];
				        if(data[arg][i] > maxY)
				                maxY = data[arg][i]; 
				        if(data[arg][++i] < minC)
				                minC = data[arg][i];
				        if(data[arg][i] > maxC)
				                maxC = data[arg][i];
				}
		}
		std::cout << "max" << maxC << " min " << minC <<std::endl;
        scaleX = (maxX - minX)/2;
        scaleY = (maxY - minY)/2;
        scaleC = (maxC - minC);
        moveX = (maxX + minX)/2 ;
        moveY = (maxY + minY)/2;
		std::cout << "scaleX" << scaleX << " scaleY " << scaleY << "moveX" << moveX << " moveY " << moveY<<std::endl;
		for(int arg = 0; arg < args; arg++)		
				for(int i = 0; i < data[arg].size();i++)
				{
				        data[arg][i] = (data[arg][i] -moveX) / scaleX;
				        data[arg][++i] = (data[arg][i] -moveY) / scaleY;
				        data[arg][++i] = (data[arg][i] -minC) / scaleC;  
				}       
}

int loadVertex(int arg, char * argv)
{
        std::cout << arg << std::endl;
                FILE* file = fopen (argv , "r");
                char wiersz[1000];
                char latlon=0;
                std::cout << "laduje\n";
                while (fgets(wiersz, 1000, file) != NULL){
                        //std::cout << wiersz << std::endl;
                        float lat,lon,ele;
                        char *p;
                        if (strstr(wiersz, "<trkpt ")){
                                 sscanf( strstr(wiersz, "lat=\"")+5, "%f", &lat);
                                 sscanf( strstr(wiersz, "lon=\"")+5, "%f", &lon);
                                 data[arg].push_back(lat);
                                 data[arg].push_back(lon);

                                 latlon = 1;
                        }
                        else if (p=strstr(wiersz, "<ele>")){
                                 sscanf( p+5, "%f</ele>", &ele); 
                                 if (latlon == 1) {
                                            data[arg].push_back(ele);
                                 }
                        }
                }

                std::cout << "done" << std::endl;
		std::cout << data[arg].size() << std::endl;
}


int main(int argc, char * argv[] )
{
		data = new std::vector < GLfloat >[2]();
		for(int i = 0; i < argc -1; i++)
        	loadVertex(i, argv[i+1]);
		resize(argc-1);

        if( !glfwInit() )
        {
                fprintf( stderr, "Failed to initialize GLFW\n" );
                return -1;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Open a window and create its OpenGL context
        window = glfwCreateWindow( 1024, 768, "Tutorial 03 - Matrices", NULL, NULL);
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
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        // Create and compile our GLSL program from the shaders
        GLuint programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );

        // Get a handle for our "MVP" uniform
        GLuint MatrixID = glGetUniformLocation(programID, "MVP");

        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model      = glm::mat4(1.0f);
        // Our ModelViewProjection : multiplication of our 3 matrices


        GLuint vertexbuffers[argc-1];
		GLuint vertexPositionID[argc-1];
		for(int i = 0; i < argc -1; i++)
		{
				glGenBuffers(1, &vertexbuffers[i]);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[i]);
				glBufferData(GL_ARRAY_BUFFER, data[i].size()* sizeof(GLfloat), &data[i].front(), GL_STATIC_DRAW);
				vertexPositionID[i] = glGetAttribLocation(programID, "vertexPosition_modelspace");
		}

        do{
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glUseProgram(programID);
                computeMatricesFromInputs();
                glm::vec3 cameraPos = getCameraPos();


                glUniform3fv(MatrixID, 1, &cameraPos[0]);
		        glEnableVertexAttribArray(0);

                for(int i = 0; i < argc -1; i++){
		            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[i]);
		            glVertexAttribPointer(
		                    vertexPositionID[i],                  // attribute. No particular reason for 0, but must match the layout in the shader.
		                    3,                  // size
		                    GL_FLOAT,           // type
		                    GL_FALSE,           // normalized?
		                    0,                  // stride
		                    (void*)0            // array buffer offset
		            );
                glDrawArrays(GL_LINE_STRIP, 0, data[i].size()/3); // 3 indices starting at 0 -> 1 trianglei
                }
				glDisableVertexAttribArray(0);

                // Swap buffers
                glfwSwapBuffers(window);
                glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed
        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                   glfwWindowShouldClose(window) == 0 );

        // Cleanup VBO and shader
		for(int i = 0; i < argc -1; i++)
        {
				glDeleteBuffers(1, &vertexbuffers[i]);
		}
        glDeleteProgram(programID);

        // Close OpenGL window and terminate GLFW
        glfwTerminate();

        return 0;
}



