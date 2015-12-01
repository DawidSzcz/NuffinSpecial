#include <GL/glew.h>
#include "TranslationVertexShader.hpp"

TranslationVertexShader::TranslationVertexShader(const char* vshader_path,const char* fshader_path)
: IShader(vshader_path,fshader_path) {
	VertexPositionID = glGetAttribLocation(CompiledProgramID, "vertexPosition_modelspace");
	VertexColorID = glGetAttribLocation(CompiledProgramID, "vertexColor");
	TranslationVectorID = glGetUniformLocation(CompiledProgramID, "translation");
}