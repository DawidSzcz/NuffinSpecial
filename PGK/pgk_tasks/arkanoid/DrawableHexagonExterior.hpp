#ifndef DRAWABLE_HEXAGON_EXTERIOR_HPP
#define DRAWABLE_HEXAGON_EXTERIOR_HPP

#include <GL/glew.h>
#include "ITranslationVertexShaderDrawable.hpp"

class DrawableHexagonExterior : public ITranslationVertexShaderDrawable {
public:
	DrawableHexagonExterior(const TranslationVertexShader* shader,
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