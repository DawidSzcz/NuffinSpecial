#include "Zad3.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "shader.hpp"
#include <array>

GLFWwindow* window;
std::vector < GLfloat > walls;
std::vector < GLint > wIndex;

#define SIZE 5

int main(int argc, char * argv[] )
{	
	std::cout<<"woot\n";
	if(makeWindow((char*)"Zad2") == -1)
		return -1;
	GLuint texture = bindImage(argv[1]);

	bool isWall[SIZE][SIZE] =  	{{true, true, true, false, false},
								 {false, false, true, false, true},
								 {true, false, false, false, true},
								 {true, false, true, false, true},
								 {true, true, true, true, true}};

 	GLuint programID1 = LoadShaders( "Transform.vertexshader", "FragmentShader.fragmentshader" );
	GLuint programID2 = LoadShaders( "Path.vertexshader", "Path.fragmentshader" );
	GLfloat vertexes[] = {
    		-1.0f, 1.0f, 0.0f, 1.0f,
     		1.0f, 1.0f, 1.0f, 1.0f,
     		-1.0f,  -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 0.0f
	};  
	GLuint indices[] = {  2, 0, 1, 2, 3, 1};
        
	GLuint VAO, VBA, EBO, VAOWALL, VBAWALL, EBOWALL;
	
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
	
	GLfloat cap = 2.0/SIZE;
	int index = 0;
	std::array<GLfloat, 12>  wall;
	std::array<GLint, 6> indexes;
	/*std::array<GLfloat, 12>  wall;
					wall = {-0.5, 0.5, 0,
						0.5, 0.5, 0,
						0.5, -0.5, 0,
						-0.5, -0.5, 0};
	walls.insert(walls.end(), (&wall.front()), (&wall.front())+12);
	std::array<GLint, 6> indexes;
	indexes = {  2, 0, 1, 2, 3, 0};
	wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);*/
	
	for(float i = -1; i < 1; i+=cap)
		for(float d = -1; d < 1; d+=cap)
			if(isWall[(int)(((i+1)*2.5)+0.1)][(int)(((d+1)*2.5)+0.1)])
			{
				//std::cout<<isWall[(int)(((i+1)*2.5)+0.1)][(int)(((d+1)*2.5)+0.1)]<<" ";
				//left
				wall = {d, i, 0,
						d, i, cap,
						d, i+cap, 0,
						d, i+cap, cap};
				walls.insert(walls.end(), (&wall.front()), (&wall.front())+12);
				indexes={index+0, index+1, index+2, index+1, index+3, index+2};
				wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
				index+=4;
				//up
				wall = {d, i, 0,
						d, i, cap,
						d+cap, i, 0,
						d+cap, i, cap};
				walls.insert(walls.end(), (&wall.front()), (&wall.front())+12);
				indexes={index+0, index+1, index+2, index+1, index+3, index+2};
				wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
				index+=4;
				
				//right
				wall = {d+cap, i, 0,
						d+cap, i, cap,
						d+cap, i+cap, 0,
						d+cap, i+cap, cap};
				walls.insert(walls.end(), (&wall.front()), (&wall.front())+12);
				indexes={index+0, index+1, index+2, index+1, index+3, index+2};
				wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
				index+=4;
				
				//down
				wall = {d+cap, i+cap, 0,
						d+cap, i+cap, cap,
						d, i+cap, 0,
						d, i+cap, cap};
				walls.insert(walls.end(), (&wall.front()), (&wall.front())+12);
				indexes={index+0, index+1, index+2, index+1, index+3, index+2};
				wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
				index+=4;
				
				//top
				wall = {d, i, cap,
						d+cap, i, cap,
						d+cap, i+cap, cap,
						d, i+cap, cap};
				walls.insert(walls.end(), (&wall.front()), (&wall.front())+12);
				indexes={index+0, index+2, index+3, index+0, index+2, index+1};
				wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
				index+=4;
		}	
				
	/*GLfloat vertexs[] = {-0.5, 0.5, 0,
						0.5, 0.5, 0,
						0.5, -0.5, 0,
						-0.5, -0.5, 0} ;
	GLuint indics[] = {  0, 2, 1, 2, 0, 3};*/

	glGenVertexArrays(1, &VAOWALL);
	glBindVertexArray(VAOWALL);
	
	int sizeOfDB = walls.size() * sizeof(walls[0]);
	int sizeOfEB = wIndex.size() * sizeof(wIndex[0]);
	glGenBuffers(1, &VBAWALL);
	glBindBuffer(GL_ARRAY_BUFFER,VBAWALL);
	glBufferData(GL_ARRAY_BUFFER, sizeOfDB, &walls.front(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &EBOWALL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOWALL);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfEB, &wIndex.front(), GL_STATIC_DRAW); 
	
	std::cout<<"\nWALLS\n";
	for(int i = 0; i < walls.size(); i++)
	{
		if(i % 12 == 0)
			std::cout<<"\n";
		std::cout<<walls[i]<<" ";
	}
	std::cout<<"\nINDEXES\n";
	for(int i = 0; i < wIndex.size(); i++)
	{
		if(i % 6 == 0)
			std::cout<<"\n";	
		std::cout<<wIndex[i]<<" ";
	}
	std::cout<<"\nSizeof data buffer: "<<sizeOfDB<<" element buffer: " << sizeOfEB <<std::endl;
	
	glVertexAttribPointer(
		               2,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		                3,                  // size
		                GL_FLOAT,           // type
		                GL_FALSE,           // normalized?
		                3*sizeof(GLfloat),                  // stride
		                (void*)0            // array buffer offset
		    );
	glEnableVertexAttribArray(2);	
	glBindVertexArray(0);
	
	//glm::mat4 cameraPos;
	//GLuint vec1 = glGetUniformLocation(programID1, "transform");
	//GLuint vec2 = glGetUniformLocation(programID2, "transform");
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		//computeMatricesFromInputs();		
		//cameraPos = getCameraPos();	
		
		glUseProgram(programID1);		
		//glUniformMatrix4fv(vec1, 1, GL_FALSE, glm::value_ptr(cameraPos));	
		glBindVertexArray(VAO);		
		glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glUseProgram(programID2);	
		//glUniformMatrix4fv(vec2, 1, GL_FALSE, glm::value_ptr(cameraPos));
		glBindVertexArray(VAOWALL);
		glDrawElements(GL_TRIANGLES, wIndex.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}
