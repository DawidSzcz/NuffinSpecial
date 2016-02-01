#ifndef ZAD3_HPP
#define ZAD3_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <vector>
#include <array>
#include <string.h>
#include <iostream>
#include <fstream>
#include "controls.hpp"
#include "shader.hpp"

extern GLfloat xpos, zpos;
extern int windowWidth, windowHeight;

extern GLFWwindow* window;
int makeWindow(int, int, char* str);
void makeWalls(char* path, int SIZE);
ILubyte bindImage(std::string path);
bool isEnd();
bool banned(GLfloat x, GLfloat y);
extern std::vector < GLfloat > walls;
extern std::vector < GLint > wIndex;
extern std::vector <std::vector<bool>> isWall;
extern int SIZE, mZ, mX;

#endif
