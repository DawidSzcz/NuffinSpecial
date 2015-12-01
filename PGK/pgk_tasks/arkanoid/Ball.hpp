#ifndef BALL_HPP
#define BALL_HPP

#include <GL/glew.h>
#include "DrawableCircle.hpp"
#include "ICollidable.hpp"
#include "IConstantVelocityMovable.hpp"

class Ball : public DrawableCircle, public ICollidable, public IConstantVelocityMovable {
public:
	Ball(	const TranslationVertexShader* shader,
			GLfloat radius=0.018,
			GLfloat colorR=0.9, GLfloat colorG=0.9, GLfloat colorB=0.8,
			GLfloat border_width=0.005,
			GLfloat borderColorR=0.1, GLfloat borderColorG=0.0, GLfloat borderColorB=0.3
	);
	virtual void SetPrimitives();
	virtual void OnCollision(ICollidable* other,Contact details);
	virtual ~Ball() { CleanupBuffers(); }
};

#endif