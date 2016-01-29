#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include <vector>
#include "BasicHeader.hpp"

class IShader;

class IDrawable {
public:
	// object translation, rotation and scale
	Transformation_t Model;

	// use these to get GPU buffers data
	virtual void GenVertices(std::vector<Vertex_t>& vertices,std::vector<TrIndex_t>& triangles) const = 0;
	virtual unsigned long int GetVerticesNum() const = 0;
	virtual unsigned long int GetTrianglesNum() const = 0;
	
	// should be set before drawing
	GLuint VertexBufferID;
	GLuint IndexBufferID;
	GLuint IndexBufferOffset = 0;

	IShader* Shader;

	// drawing call to OpenGL
	// VertexBufferID and IndexBufferID should be already bound
	// Shader should be set
	// all uniforms should be send
	//virtual void DrawCall() const { glDrawElements(GL_TRIANGLES,GetTrianglesNum()*3,INDEX_TYPE,(void*)IndexBufferOffset); }

	virtual ~IDrawable() {}
};

#endif