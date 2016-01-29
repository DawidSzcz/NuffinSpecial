#include "Zad2.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "shader.hpp"
#include "controls2.hpp"
#include <array>

GLFWwindow* window;
std::vector < GLfloat > walls;
std::vector < GLfloat > wIndex;

int main(int argc, char * argv[] )
{	
	int x = 5;
	int tab[x] = {1,2,3,4,5};
	std::vector < GLfloat > walls;  walls;
	std::array<GLfloat, 15>  wall;
	wall = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	walls.insert(walls.end(), (&wall.front()), (&wall.front())+15);
	for(int i = 0; i < 15; i++)
		std::cout<<walls[i]<<" ";
		
	bool isWall[5][5] =  	{{true, true, true, true, false},
						 {false, false, true, false, true},
						 {true, false, false, false, true},
						 {true, false, true, false, true},
						 {true, false, true, false, true}};
						 
						 
	for(int i = 0; i < 5; i++)
		for(int d = 0; d < 5; d++)
			;//std::cout<<isWall[i][d];
	std::cout<<"\n"<<sizeof(walls) << " " << walls.size();	
}
