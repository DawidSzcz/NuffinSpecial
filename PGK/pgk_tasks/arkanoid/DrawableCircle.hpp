#ifndef DRAWABLE_CIRCLE_HPP
#define DRAWABLE_CIRCLE_HPP

#include <GL/glew.h>
#include "ITranslationVertexShaderDrawable.hpp"

class DrawableCircle : public ITranslationVertexShaderDrawable {
public:
	DrawableCircle(	const TranslationVertexShader* shader,
					GLfloat radius,
					GLfloat colorR, GLfloat colorG, GLfloat colorB,
					GLfloat border_width=0.0,
					GLfloat borderColorR=0.0, GLfloat borderColorG=0.0, GLfloat borderColorB=0.0
	);
	virtual void SetupBuffers();
	virtual void Draw() const;
	virtual void CleanupBuffers();
protected:
	GLfloat r,border;
	GLfloat colR,colG,colB;
	GLfloat bColR,bColG,bColB;
	GLuint foundationVertexbufferID,foundationColorbufferID;
	GLuint realVertexbufferID,realColorbufferID;
	unsigned int vertices_num;
};

#endif