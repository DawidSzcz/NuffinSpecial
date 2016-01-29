#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ITranslationVertexShaderDrawable.hpp"
#include "TranslationVertexShader.hpp"
#include "DrawableHexagonExterior.hpp"

DrawableHexagonExterior::DrawableHexagonExterior(	const TranslationVertexShader* shader,
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

void DrawableHexagonExterior::SetupBuffers() {
	GLfloat alpha = M_PI*0.5;
	const int ex_n = 7;
	const int n = 2*ex_n;
	GLfloat p = r-border;

	GLfloat ex[ex_n*2] = {
		-1.0, -1.0,
		-1.0,  1.0,
		 0.0,  1.0,
		 1.0,  1.0,
		 1.0, -1.0,
		 0.0, -1.0,
		-1.0, -1.0,
	};

	GLfloat foundation[n*3];
	GLfloat real[n*3];
	for(int i=0 ; i < n ; i++) {
		if(i%2 == 0) {
			int j=i/2;
			foundation[3*i+0] = ex[j*2+0];
			foundation[3*i+1] = ex[j*2+1];
			foundation[3*i+2] = 0.0;

			real[3*i+0] = ex[j*2+0];
			real[3*i+1] = ex[j*2+1];
			real[3*i+2] = 0.0;
		} else {
			int j = ((i-1)/2) % 6;

			GLfloat x = glm::sin((M_PI*2*j)/6 - alpha);
			GLfloat y = glm::cos((M_PI*2*j)/6 - alpha);

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

void DrawableHexagonExterior::Draw() const {
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
	
void DrawableHexagonExterior::CleanupBuffers() {
	deleteBuffer(foundationVertexbufferID);
	deleteBuffer(foundationColorbufferID);
	deleteBuffer(realVertexbufferID);
	deleteBuffer(realColorbufferID);
}