#ifndef BASIC_HEADER_HPP
#define BASIC_HEADER_HPP

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <cassert>

#define COORD_TYPE GL_FLOAT
typedef GLfloat Coord_t;
typedef glm::vec3 Position_t;
typedef glm::mat4 Transformation_t;

#define PRIMCOLUOR_TYPE GL_FLOAT
typedef GLfloat PrimColour_t;
typedef glm::vec3 Colour_t;

#define NCOORD_TYPE GL_FLOAT
typedef GLfloat NCoord_t; 
typedef glm::vec3 Normal_t;

struct Vertex_t {
	Position_t position;
	Colour_t colour;
	Normal_t normal;

	Vertex_t(Position_t p,Colour_t c,Normal_t n)
	: position(p), colour(c), normal(n) {}

	Vertex_t(	GLfloat x,GLfloat y,GLfloat z,
				GLfloat r,GLfloat g,GLfloat b,
				GLfloat nx,GLfloat ny,GLfloat nz)
	: position(x,y,z), colour(r,g,b), normal(nx,ny,nz) {}
};

#define INDEX_TYPE GL_UNSIGNED_INT
typedef GLuint Index_t;
typedef glm::uvec3 TrIndex_t;

typedef double Time_t;

const Coord_t eps = 0.0001;

#endif