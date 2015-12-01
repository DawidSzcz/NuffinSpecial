#ifndef TYPES_HPP
#define TYPES_HPP

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#define COORD_TYPE GL_FLOAT
typedef GLfloat Coord_t;
typedef glm::vec2 TexPosition_t;
typedef glm::vec3 Position_t;
typedef glm::vec3 Vector_t;
typedef glm::mat4 Matrix_t;

#define PRIMCOLUOR_TYPE GL_FLOAT
typedef GLfloat PrimColour_t;
typedef glm::vec3 Colour_t;

struct Vertex_t {
	Position_t position;
	TexPosition_t texUV;
	Vector_t normal;

	Vertex_t(Position_t p,TexPosition_t uv,Vector_t n)
	: position(p), texUV(uv), normal(n) {}
};

#define INDEX_TYPE GL_UNSIGNED_INT
typedef GLuint Index_t;
typedef glm::uvec3 Face_t;

typedef double Time_t;

const Coord_t eps = 0.0001;

#endif