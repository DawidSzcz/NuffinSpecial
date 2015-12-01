#ifndef DRAWABLE_RECTANGLE_HPP
#define DRAWABLE_RECTANGLE_HPP

#include <GL/glew.h>
#include "ITranslationVertexShaderDrawable.hpp"

class DrawableRectangle : public ITranslationVertexShaderDrawable {
public:
	DrawableRectangle(	const TranslationVertexShader* shader,
						GLfloat width, GLfloat height,
						GLfloat colorR, GLfloat colorG, GLfloat colorB,
						GLfloat border_width=0.0,
						GLfloat borderColorR=0.0, GLfloat borderColorG=0.0, GLfloat borderColorB=0.0
	);
	virtual void SetupBuffers();
	virtual void Draw() const;
	virtual void CleanupBuffers();
protected:
	GLfloat w,h,border;
	GLfloat colR,colG,colB;
	GLfloat bColR,bColG,bColB;
	GLuint foundationVertexbufferID,foundationColorbufferID;
	GLuint realVertexbufferID,realColorbufferID;
	unsigned int vertices_num;
};

#endif