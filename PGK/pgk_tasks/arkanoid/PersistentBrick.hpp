#ifndef PERSISTENT_BRICK_HPP
#define PERSISTENT_BRICK_HPP

#include <GL/glew.h>
#include "DrawableRectangle.hpp"
#include "ICollidable.hpp"
#include "IObservable.hpp"

class PersistentBrick : public DrawableRectangle, public ICollidable, public IObservable {
public:
	PersistentBrick(const TranslationVertexShader* shader,
					GLfloat width=0.05, GLfloat height=0.05,
					GLfloat colorR=1.0, GLfloat colorG=0.0, GLfloat colorB=0.0,
					GLfloat border_width=0.002,
					GLfloat borderColorR=0.1, GLfloat borderColorG=0.0, GLfloat borderColorB=0.3
	);
	virtual void SetPrimitives();
	virtual void OnCollision(ICollidable* other,Contact details);
	virtual ~PersistentBrick() { CleanupBuffers(); }
};

#endif