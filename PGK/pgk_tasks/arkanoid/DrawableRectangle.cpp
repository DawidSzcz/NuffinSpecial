#include <GL/glew.h>
#include "ITranslationVertexShaderDrawable.hpp"
#include "TranslationVertexShader.hpp"
#include "DrawableRectangle.hpp"

DrawableRectangle::DrawableRectangle(	const TranslationVertexShader* shader,
										GLfloat width, GLfloat height,
										GLfloat colorR, GLfloat colorG, GLfloat colorB,
										GLfloat border_width,
										GLfloat borderColorR, GLfloat borderColorG, GLfloat borderColorB
)
:	ITranslationVertexShaderDrawable(shader),
	w(width), h(height),
	border(border_width),
	colR(colorR), colG(colorG), colB(colorB),
	bColR(borderColorR), bColG(borderColorG), bColB(borderColorB)
{}

void DrawableRectangle::SetupBuffers() {
	GLfloat a = w*0.5, b = h*0.5;
	GLfloat foundation[4*3] = {
		-a, -b, 0.0,
		-a,  b, 0.0,
		 a, -b, 0.0,
		 a,  b, 0.0,
	};

	a -= border; b -= border;
	GLfloat real[4*3] = {
		-a, -b, 0.0,
		-a,  b, 0.0,
		 a, -b, 0.0,
		 a,  b, 0.0,
	};

	GLfloat f_colors[4*3];
	GLfloat r_colors[4*3];
	for(int i=0 ; i < 4 ; i++) {
		f_colors[3*i+0] = bColR;
		f_colors[3*i+1] = bColG;
		f_colors[3*i+2] = bColB;

		r_colors[3*i+0] = colR;
		r_colors[3*i+1] = colG;
		r_colors[3*i+2] = colB;
	}

	vertices_num = 4;
	foundationVertexbufferID = newBuffer(foundation,sizeof(foundation));
	realVertexbufferID = newBuffer(real,sizeof(real));
	foundationColorbufferID = newBuffer(f_colors,sizeof(f_colors));
	realColorbufferID = newBuffer(r_colors,sizeof(r_colors));
}

void DrawableRectangle::Draw() const {
	glUseProgram(sh->CompiledProgramID); //set shader
	glUniform3fv(sh->TranslationVectorID,1,&Position[0]); //set uniform

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(sh->VertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, foundationVertexbufferID);
	glVertexAttribPointer(
		sh->VertexPositionID,	// The attribute we want to configure
		3,						// size
		GL_FLOAT,				// type
		GL_FALSE,				// normalized?
		0,						// stride
		(void*)0				// array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(sh->VertexColorID);
	glBindBuffer(GL_ARRAY_BUFFER, foundationColorbufferID);
	glVertexAttribPointer(
		sh->VertexColorID,	// The attribute we want to configure
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		0,					// stride
		(void*)0			// array buffer offset
	);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices_num);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(sh->VertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, realVertexbufferID);
	glVertexAttribPointer(
		sh->VertexPositionID,	// The attribute we want to configure
		3,						// size
		GL_FLOAT,				// type
		GL_FALSE,				// normalized?
		0,						// stride
		(void*)0				// array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(sh->VertexColorID);
	glBindBuffer(GL_ARRAY_BUFFER, realColorbufferID);
	glVertexAttribPointer(
		sh->VertexColorID,	// The attribute we want to configure
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		0,					// stride
		(void*)0			// array buffer offset
	);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices_num);

	glDisableVertexAttribArray(sh->VertexPositionID);
	glDisableVertexAttribArray(sh->VertexColorID);
}

void DrawableRectangle::CleanupBuffers() {
	deleteBuffer(foundationVertexbufferID);
	deleteBuffer(foundationColorbufferID);
	deleteBuffer(realVertexbufferID);
	deleteBuffer(realColorbufferID);
}