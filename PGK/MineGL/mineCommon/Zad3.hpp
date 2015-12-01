#ifndef ZAD2_HPP
#define ZAD2_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>

extern GLFWwindow* window;
int makeWindow(char* str);
ILubyte bindImage(std::string path);

#endif
