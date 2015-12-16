#include "Zad3.hpp"

GLfloat xpos, zpos;
GLFWwindow* window;
std::vector < GLfloat > walls;
std::vector < GLint > wIndex;
std::vector <std::vector<bool>> isWall;
int SIZE, mZ, mX;

void makeWalls(char* path)
{
	std::array<GLfloat, 20>  wall;
	std::array<GLint, 6> indexes;
	FILE* file = fopen (path , "r");
	
	int index = 0, ret; int i = -1;
	GLfloat x = -1.0, y = 1.0;
	char c;
	
	ret = fscanf(file, "%d\n", &SIZE);
	ret = fscanf(file, "%c", &c);
	
	GLfloat cap = 2.0/SIZE;
	isWall.push_back(std::vector<bool>());
	while(ret && ++i < SIZE*SIZE)
	{
		std::cout<<c<<" "<<x<<" "<<y<<" vector: " << i/SIZE<<std::endl;
		if(c == '\n')
		{
			x = -1.0; y -= cap; i--;
			isWall.push_back(std::vector<bool>());
		}
		if(c == 's')
		{
			isWall[i/SIZE].push_back(false);
			xpos = -x - cap/2;
			zpos = y - cap/2;
		} 
		if(c == 'm')
		{
			isWall[i/SIZE].push_back(false);
			mX = i/SIZE;
			mZ = i%SIZE;
		} 
		if(c == 'w' )
		{
			isWall[i/SIZE].push_back(true);
			//left
			wall = {x, y, 0.0f, 0.0f, 0.0f,
					x, y, cap, 0.0f, 1.0f,
					x, y-cap, 0.0f, 1.0f, 0.0f,
					x, y-cap, cap, 1.0f, 1.0f};
			walls.insert(walls.end(), (&wall.front()), (&wall.front())+wall.size());
			indexes={index+0, index+1, index+2, index+1, index+3, index+2};
			wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
			index+=4;
			//up
			wall = {x, y, 0.0f, 0.0f, 0.0f,
					x, y, cap, 0.0f, 1.0f,  
					x+cap, y, 0.0f, 1.0f, 0.0f,
					x+cap, y, cap, 1.0f, 1.0f};
			walls.insert(walls.end(), (&wall.front()), (&wall.front())+wall.size());
			indexes={index+0, index+1, index+2, index+1, index+3, index+2};
			wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
			index+=4;
			
			//right
			wall = {x+cap, y, 0.0f, 0.0f, 0.0f,
					x+cap, y, cap, 0.0f, 1.0f,
					x+cap, y-cap, 0.0f, 1.0f, 0.0f,
					x+cap, y-cap, cap, 1.0f, 1.0f};
			walls.insert(walls.end(), (&wall.front()), (&wall.front())+wall.size());
			indexes={index+0, index+1, index+2, index+1, index+3, index+2};
			wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
			index+=4;
			
			//down
			wall = {x+cap, y-cap, 0.0f, 1.0f, 0.0f,
					x+cap, y-cap, cap, 1.0f, 1.0f,
					x, y-cap, 0.0f, 0.0f, 0.0f,
					x, y-cap, cap, 0.0f, 1.0f};
			walls.insert(walls.end(), (&wall.front()), (&wall.front())+wall.size());
			indexes={index+0, index+1, index+2, index+1, index+3, index+2};
			wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
			index+=4;
			
			//top
			wall = {x, y, cap, 0.0f, 0.0f,
					x+cap, y, cap, 1.0f, 0.0f,
					x+cap, y-cap, cap, 1.0f, 1.0f,
					x, y-cap, cap, 0.0f, 1.0f};
			walls.insert(walls.end(), (&wall.front()), (&wall.front())+wall.size());
			indexes={index+0, index+2, index+3, index+0, index+2, index+1};
			wIndex.insert(wIndex.end(), (&indexes.front()), (&indexes.front())+6);
			index+=4;
		}
		if( c != '\n')	
			x+=cap;
		if(c == 'e')
			isWall[i/SIZE].push_back(false);
		ret = fscanf(file, "%c", &c);
	}
	for(int i = 0; i < isWall.size(); i++)
	{
		for(int d = 0; d < isWall[i].size(); d++)
			std::cout<<isWall[i][d]<<" ";
		std::cout<<"\n";
	}
	std::cout<<"Meta:" << mX << " " << mZ ;
}


int main(int argc, char * argv[] )
{	
	if(makeWindow((char*)"Zad3") == -1)
		return -1;
	GLuint wTexture = bindImage("mur2.png");
	GLuint texture = bindImage("floor.png");
	
	makeWalls((char*)"sth");
	std::cout<<"tutut"<< std::endl;

 	GLuint programID1 = LoadShaders( "Transform.vertexshader", "FragmentShader.fragmentshader" );
	GLuint programID2 = LoadShaders( "Path.vertexshader", "Path.fragmentshader" );
	GLfloat vertexes[] = {
    		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
     		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f
	};  
	GLuint indices[] = {  2, 0, 1, 2, 3, 1};

	GLfloat meta[] = {
    		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
     		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f
	}; 
        
	GLuint VAO, VBA, EBO, VAOWALL, VBAWALL, EBOWALL;
	
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
	glGenBuffers(1, &VBA);
    glBindBuffer(GL_ARRAY_BUFFER,VBA);
	glBufferData(GL_ARRAY_BUFFER, 20* sizeof(GLfloat), vertexes, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
	glVertexAttribPointer(
                    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    5*sizeof(GLfloat),                  // stride
                    (void*)0            // array buffer offset
        );
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
                    1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    2,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    5*sizeof(GLfloat),                  // stride
                    (void*)(3*sizeof(GLfloat))           // array buffer offset
        );
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); 

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
	


	
	glVertexAttribPointer(
                    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    5*sizeof(GLfloat),                  // stride
                    (void*)0            // array buffer offset
        );
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
                    1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    2,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    5*sizeof(GLfloat),                  // stride
                    (void*)(3*sizeof(GLfloat))           // array buffer offset
        );
	glEnableVertexAttribArray(1);	
	glBindVertexArray(0);
	
	glm::mat4 cameraPos;
	GLuint vec1 = glGetUniformLocation(programID1, "transform");
	glEnable(GL_DEPTH_TEST);  
	
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		computeMatricesFromInputs();		
		cameraPos = getCameraPos();	
		
		glUseProgram(programID1);		
		glUniformMatrix4fv(vec1, 1, GL_FALSE, glm::value_ptr(cameraPos));	
		glBindVertexArray(VAO);		
		glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
		glBindVertexArray(VAOWALL);
		glBindTexture(GL_TEXTURE_2D, wTexture);
		glDrawElements(GL_TRIANGLES, wIndex.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		if(isEnd())
		{
			std::cout <<" Wygrałeś";
			glfwTerminate();
			return 0;
		}

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}
