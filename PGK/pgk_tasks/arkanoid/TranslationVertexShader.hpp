#ifndef TRANSLATION_VERTEX_SHADER_HPP
#define TRANSLATION_VERTEX_SHADER_HPP

#include <GL/glew.h>
#include "IShader.hpp"

class TranslationVertexShader : public IShader {
public:
	TranslationVertexShader(const char* vshader_path,const char* fshader_path);
	GLuint VertexPositionID;
	GLuint VertexColorID;
	GLuint TranslationVectorID;
};

#endif