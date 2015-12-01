#include <GL/glew.h>
#include "IDrawable.hpp"

GLuint IDrawable::newBuffer(void* bufferdata,unsigned int size) {
	GLuint res;
	glGenBuffers(1, &res);
	glBindBuffer(GL_ARRAY_BUFFER, res);
	glBufferData(GL_ARRAY_BUFFER, size, bufferdata, GL_STATIC_DRAW);
	return res;
}