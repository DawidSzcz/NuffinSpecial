#ifndef MODEL_HPP
#define MODEL_HPP

#include <tuple>
#include <vector>
#include <string>
#include "types.hpp"

class Mesh {
public:
	// buffers
	std::vector<Vertex_t> Vertices;
	std::vector<Face_t> Faces;
	GLuint VBO=0;
	GLuint IBO=0;
	void Bind(); //const
	void Unbind() const;
	Mesh() {}
	Mesh(std::vector<Vertex_t> vertices, std::vector<Face_t> faces);
};

class Material {
public:
	bool HasTexture;
	GLuint TextureBO;
	std::string TextureFile;
	bool TextureLoaded=false;
	void Bind();
	void Unbind();
	Material();
	Material(std::string tex);
};

class Model {
public:
	std::vector< std::tuple<Matrix_t,Mesh*,Material*> > Meshes;
};

#endif