#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ITranslationVertexShaderDrawable.hpp"
#include "TranslationVertexShader.hpp"
#include "DrawableCircle.hpp"

DrawableCircle::DrawableCircle(	const TranslationVertexShader* shader,
								GLfloat radius,
								GLfloat colorR, GLfloat colorG, GLfloat colorB,
								GLfloat border_width,
								GLfloat borderColorR, GLfloat borderColorG, GLfloat borderColorB
)
:	ITranslationVertexShaderDrawable(shader),
	r(radius),
	border(border_width),
	colR(colorR), colG(colorG), colB(colorB),
	bColR(borderColorR), bColG(borderColorG), bColB(borderColorB)
{}

void DrawableCircle::SetupBuffers() {
	const int edges_n = 16;
	const int n = edges_n+2;
	GLfloat p = r-border;

	GLfloat foundation[n*3];
	GLfloat real[n*3];
	for(int i=0 ; i < n ; i++) {
		if(i == 0) {
			foundation[3*i+0] = 0.0;
			foundation[3*i+1] = 0.0;
			foundation[3*i+2] = 0.0;

			real[3*i+0] = 0.0;
			real[3*i+1] = 0.0;
			real[3*i+2] = 0.0;
		} else {
			int j = i%edges_n;

			GLfloat x = glm::cos((M_PI*2*j)/edges_n);
			GLfloat y = glm::sin((M_PI*2*j)/edges_n);

			foundation[3*i+0] = x*r;
			foundation[3*i+1] = y*r;
			foundation[3*i+2] = 0.0;

			real[3*i+0] = x*p;
			real[3*i+1] = y*p;
			real[3*i+2] = 0.0;
		}
	}

	GLfloat f_colors[n*3];
	GLfloat r_colors[n*3];
	for(int i=0 ; i < n ; i++) {
		f_colors[3*i+0] = bColR;
		f_colors[3*i+1] = bColG;
		f_colors[3*i+2] = bColB;

		r_colors[3*i+0] = colR;
		r_colors[3*i+1] = colG;
		r_colors[3*i+2] = colB;
	}

	vertices_num = n;
	foundationVertexbufferID = newBuffer(foundation,sizeof(foundation));
	realVertexbufferID = newBuffer(real,sizeof(real));
	foundationColorbufferID = newBuffer(f_colors,sizeof(f_colors));
	realColorbufferID = newBuffer(r_colors,sizeof(r_colors));
}

void DrawableCircle::Draw() const {
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

	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices_num);

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

	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices_num);

	glDisableVertexAttribArray(sh->VertexPositionID);
	glDisableVertexAttribArray(sh->VertexColorID);
}

void DrawableCircle::CleanupBuffers() {
	deleteBuffer(foundationVertexbufferID);
	deleteBuffer(foundationColorbufferID);
	deleteBuffer(realVertexbufferID);
	deleteBuffer(realColorbufferID);
}