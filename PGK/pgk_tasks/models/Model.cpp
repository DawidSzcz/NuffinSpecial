#include <SOIL/SOIL.h>
#include "Model.hpp"

#include <iostream>

extern GLuint programID;

void Mesh::Bind() {// const {
	if(VBO == IBO) {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_t)*Vertices.size(), Vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Face_t)*Faces.size(), Faces.data(), GL_STATIC_DRAW);
	}

	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	glEnableVertexAttribArray(vertexPosition_modelspaceID);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(
		vertexPosition_modelspaceID,
		3,
		COORD_TYPE,
		GL_FALSE,
		sizeof(Vertex_t),
		(void*)offsetof(Vertex_t,position)
	);

	GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(
		vertexUVID,
		2,
		COORD_TYPE,
		GL_FALSE,
		sizeof(Vertex_t),
		(void *)offsetof(Vertex_t,texUV)
	);

	GLuint vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");
	glEnableVertexAttribArray(vertexNormal_modelspaceID);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(
		vertexNormal_modelspaceID,
		3,
		COORD_TYPE,
		GL_FALSE,
		sizeof(Vertex_t),
		(void *)offsetof(Vertex_t,normal)
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
}

void Mesh::Unbind() const {
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	glDisableVertexAttribArray(vertexPosition_modelspaceID);

	GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
	glDisableVertexAttribArray(vertexUVID);

	GLuint vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");
	glDisableVertexAttribArray(vertexNormal_modelspaceID);
}

void Material::Bind() {
	if(!HasTexture) return;

	if(!TextureLoaded) {
		TextureBO = SOIL_load_OGL_texture (
                TextureFile.data(),
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS
				| SOIL_FLAG_POWER_OF_TWO
				| SOIL_FLAG_TEXTURE_REPEATS
				| SOIL_FLAG_COMPRESS_TO_DXT
             	| SOIL_FLAG_NTSC_SAFE_RGB
				| SOIL_FLAG_INVERT_Y
        );
            
        if(TextureBO == 0) {
            throw "Loading texture failed";
            //SOIL_last_result() );
        }

        TextureLoaded = true;
	}

	GLuint TextureID  = glGetUniformLocation(programID, "TextureSampler");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureBO);
	glUniform1i(TextureID, 0);
}

void Material::Unbind() {
}

Material::Material(std::string tex)
: HasTexture(true), TextureFile(tex) {}

Material::Material()
: HasTexture(false) {}

Mesh::Mesh(std::vector<Vertex_t> vertices, std::vector<Face_t> faces)
: Vertices(vertices), Faces(faces) {}
