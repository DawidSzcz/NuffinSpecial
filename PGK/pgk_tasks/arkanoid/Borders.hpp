#ifndef BORDERS_HPP
#define BORDERS_HPP

#include <GL/glew.h>
#include "DrawableHexagonExterior.hpp"
#include "ICollidable.hpp"

class Borders : public DrawableHexagonExterior, public ICollidable {
public:
	Borders(const TranslationVertexShader* shader,
			GLfloat radius=0.99,
			GLfloat colorR=0.0, GLfloat colorG=0.0, GLfloat colorB=0.0,
			GLfloat border_width=0.0,
			GLfloat borderColorR=0.0, GLfloat borderColorG=0.0, GLfloat borderColorB=0.0
	);
	virtual void SetPrimitives();
	virtual void OnCollision(ICollidable* other,Contact details);
	virtual ~Borders() { CleanupBuffers(); }
};

#endif