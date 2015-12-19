#include "Zad2.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

#include "shader.hpp"
#include "controls.hpp"

GLFWwindow* window;
std::vector < GLfloat >* data;

int main(int argc, char * argv[] )
{	
	if(makeWindow((char*)"Zad2") == -1)
		return -1;

	std::string path = argv[2];
	GLuint texture = bindImage(path);

	data = new std::vector < GLfloat >[argc-3]();
	for(int i = 0; i < argc -3; i++)
        	loadVertex(i, argv[i+3]);
	resize(argc-3, argv[1]);

 	GLuint programID1 = LoadShaders( "Transform.vertexshader", "FragmentShader.fragmentshader" );
	GLuint programID2 = LoadShaders( "Path.vertexshader", "Path.fragmentshader" );
	GLfloat vertexes[] = {
    		-1.0, 1.0f, 0.0f, 1.0f,
     		1.0, 1.0f, 1.0f, 1.0f,
     		-1.0,  -1.0f, 0.0f, 0.0f,
			1.0, -1.0f, 1.0f, 0.0f
	};  
	GLuint indices[] = {  2, 0, 1, 2, 3, 1};
        
	GLuint VAO, VBA, EBO, VAOPATH[argc-3][2], VBAPATH[argc-3][2];
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
	glGenBuffers(1, &VBA);
    glBindBuffer(GL_ARRAY_BUFFER,VBA);
	glBufferData(GL_ARRAY_BUFFER, 16* sizeof(GLfloat), vertexes, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
	glVertexAttribPointer(
                    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    2,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    4*sizeof(GLfloat),                  // stride
                    (void*)0            // array buffer offset
        );
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
                    1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    2,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    4*sizeof(GLfloat),                  // stride
                    (void*)(2*sizeof(GLfloat))           // array buffer offset
        );
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); 
	for(int i = 0; i < argc -3; i++)
	{
		glGenVertexArrays(1, &VAOPATH[i][0]);
		glBindVertexArray(VAOPATH[i][0]);
		glGenBuffers(1, &VBAPATH[i][0]);
		glBindBuffer(GL_ARRAY_BUFFER,VBAPATH[i][0]);
		glBufferData(GL_ARRAY_BUFFER, data[i].size()* sizeof(GLfloat), &data[i].front(), GL_STATIC_DRAW);
		glVertexAttribPointer(
		               2,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		                3,                  // size
		                GL_FLOAT,           // type
		                GL_FALSE,           // normalized?
		                0,                  // stride
		                (void*)0            // array buffer offset
		    );
		glEnableVertexAttribArray(2);	
		glBindVertexArray(0);
		
		glGenVertexArrays(1, &VAOPATH[i][1]);
		glBindVertexArray(VAOPATH[i][1]);
		glGenBuffers(1, &VBAPATH[i][1]);
		glBindBuffer(GL_ARRAY_BUFFER,VBAPATH[i][1]);
		glBufferData(GL_ARRAY_BUFFER, data[i].size()* sizeof(GLfloat), &data[i].front(), GL_STATIC_DRAW);
		glVertexAttribPointer(
		                2,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		                3,                  // size
		                GL_FLOAT,           // type
		                GL_FALSE,           // normalized?
		                6*sizeof(GLfloat),                  // stride
		                (void*)0           // array buffer offset
		    );
		glEnableVertexAttribArray(2);	
		glBindVertexArray(0);
	}
	
	glm::mat4 cameraPos;
	GLfloat cosin;
	GLuint tr1 = glGetUniformLocation(programID1, "transform");
	GLuint tr2 = glGetUniformLocation(programID2, "transform");
	GLuint cos1 = glGetUniformLocation(programID1, "cos");
	GLuint cos2 = glGetUniformLocation(programID2, "cos");
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		computeMatricesFromInputs();		
		cameraPos = getCameraPos();	
		cosin = getCosin(getYCord());
		
		glUseProgram(programID1);		
		glUniformMatrix4fv(tr1, 1, GL_FALSE, glm::value_ptr(cameraPos));
		glUniform1f(cos1, cosin);
		glBindVertexArray(VAO);		
		glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
		glUseProgram(programID2);	
		glUniformMatrix4fv(tr2, 1, GL_FALSE, glm::value_ptr(cameraPos));
		glUniform1f(cos2, cosin);
		for(int i = 0; i < argc -3; i++)
		{
			//std::cout<<i<<std::endl;
			if(!is3d())
			{
				glBindVertexArray(VAOPATH[i][1]);
				glBufferData(GL_ARRAY_BUFFER, data[i].size()* sizeof(GLfloat), &data[i].front(), GL_STATIC_DRAW);	
				glDrawArrays(GL_LINE_STRIP, 0, data[i].size()/6);
			}
			else
			{
				glBindVertexArray(VAOPATH[i][0]);
				glBufferData(GL_ARRAY_BUFFER, data[i].size()* sizeof(GLfloat), &data[i].front(), GL_STATIC_DRAW);	
				glDrawArrays(GL_TRIANGLE_STRIP, 0, data[i].size()/3);		
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}
