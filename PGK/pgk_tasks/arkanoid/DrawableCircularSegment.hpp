#ifndef DRAWABLE_CIRCULAR_SEGMENT_HPP
#define DRAWABLE_CIRCULAR_SEGMENT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ITranslationVertexShaderDrawable.hpp"

class DrawableCircularSegment : public ITranslationVertexShaderDrawable {
public:
	DrawableCircularSegment(const TranslationVertexShader* shader,
							GLfloat radius, GLfloat central_angle,
							GLfloat colorR, GLfloat colorG, GLfloat colorB,
							GLfloat border_width=0.0,
							GLfloat borderColorR=0.0, GLfloat borderColorG=0.0, GLfloat borderColorB=0.0
	);
	virtual void SetupBuffers();
	virtual void Draw() const;
	virtual void CleanupBuffers();
protected:
	GLfloat r,angle,border;
	glm::vec3 circle_center_pos;
	GLfloat colR,colG,colB;
	GLfloat bColR,bColG,bColB;
	GLuint foundationVertexbufferID,foundationColorbufferID;
	GLuint realVertexbufferID,realColorbufferID;
	unsigned int vertices_num;
};

#endif