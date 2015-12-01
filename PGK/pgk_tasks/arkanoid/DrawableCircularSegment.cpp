#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ITranslationVertexShaderDrawable.hpp"
#include "TranslationVertexShader.hpp"
#include "DrawableCircularSegment.hpp"

DrawableCircularSegment::DrawableCircularSegment(	const TranslationVertexShader* shader,
													GLfloat radius, GLfloat central_angle,
													GLfloat colorR, GLfloat colorG, GLfloat colorB,
													GLfloat border_width,
													GLfloat borderColorR, GLfloat borderColorG, GLfloat borderColorB
)
:	ITranslationVertexShaderDrawable(shader),
	r(radius), angle(central_angle),
	border(border_width),
	circle_center_pos(glm::vec3(0.0,-glm::cos(angle*0.5)*r,0.0)),
	colR(colorR), colG(colorG), colB(colorB),
	bColR(borderColorR), bColG(borderColorG), bColB(borderColorB)
{}

void DrawableCircularSegment::SetupBuffers() {
	GLfloat alpha = angle*0.5;
	const int edges_n = 6;
	const int n = edges_n+2;
	GLfloat p = r-border;

	GLfloat foundation[3*n];
	GLfloat real[3*n];
	for(int i=0 ; i < n ; i++) {
		if(i == 0) {
			foundation[3*i+0] = 0.0;
			foundation[3*i+1] = 0.0;
			foundation[3*i+2] = 0.0;

			real[3*i+0] = 0.0;
			real[3*i+1] = 0.0;
			real[3*i+2] = 0.0;
		} else {
			GLfloat x = glm::sin((angle*(i-1))/edges_n - alpha);
			GLfloat y = glm::cos((angle*(i-1))/edges_n - alpha);

			foundation[3*i+0] = x*r + circle_center_pos[0];
			foundation[3*i+1] = y*r + circle_center_pos[1];
			foundation[3*i+2] = 0.0 + circle_center_pos[2];

			real[3*i+0] = x*p + circle_center_pos[0];
			real[3*i+1] = y*p + circle_center_pos[1];
			real[3*i+2] = 0.0 + circle_center_pos[2];

			if(i == 1 || i == n-1) {
				foundation[3*i+1] = real[3*i+1] = 0.0;
			}
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

void DrawableCircularSegment::Draw() const {
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

void DrawableCircularSegment::CleanupBuffers() {
	deleteBuffer(foundationVertexbufferID);
	deleteBuffer(foundationColorbufferID);
	deleteBuffer(realVertexbufferID);
	deleteBuffer(realColorbufferID);
}