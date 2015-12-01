#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include <GL/glew.h>
#include "IPositionable.hpp"

class IDrawable : public virtual IPositionable {
public:
	virtual void SetupBuffers() = 0;
	virtual void Draw() const = 0;
	virtual void CleanupBuffers() = 0;
	static GLuint newBuffer(void* bufferdata,unsigned int size);
	static void deleteBuffer(GLuint bufferID) { glDeleteBuffers(1, &bufferID); }
};

#endif