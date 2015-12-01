#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <GL/glew.h>
#include "DrawableCircularSegment.hpp"
#include "ICollidable.hpp"
#include "IConstantVelocityMovable.hpp"

class Paddle : public DrawableCircularSegment, public ICollidable, public IConstantVelocityMovable {
public:
	Paddle(	const TranslationVertexShader* shader,
			GLfloat radius=0.07, GLfloat central_angle=M_PI*0.9,
			GLfloat colorR=0.03, GLfloat colorG=0.0, GLfloat colorB=0.25,
			GLfloat border_width=0.005,
			GLfloat borderColorR=1.0, GLfloat borderColorG=1.0, GLfloat borderColorB=0.2
	);
	virtual void SetPrimitives();
	virtual void OnCollision(ICollidable* other,Contact details);
	virtual ~Paddle() { CleanupBuffers(); }
};

#endif