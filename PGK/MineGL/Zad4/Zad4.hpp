#ifndef ZAD2_HPP
#define ZAD2_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm> 
#include "shader.hpp"
#include "controls.hpp"

extern GLFWwindow* window;
extern int windowWidth, windowHeight;
extern float** heights;
extern int rowsNum, colsNum;
extern std::vector<GLfloat> cords;
extern std::vector<glm::vec3> normals;
extern std::vector<std::vector<GLint>> elems;

int makeWindow(int x, int y, char* str);
int getPrecision();
ILubyte bindImage(std::string path);
void readFile(std::string fName);
void genElements(int x);
glm::vec3 getPosition();
glm::mat4 getModel();

#endif
