#include <GL/glew.h>
#include "common/shader.hpp"
#include "IShader.hpp"

IShader::IShader(const char* vshader_path,const char* fshader_path)
: VShader(vshader_path), FShader(fshader_path) {
	CompiledProgramID = LoadShaders(VShader,FShader);
}