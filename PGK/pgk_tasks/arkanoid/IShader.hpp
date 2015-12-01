#ifndef ISHADER_HPP
#define ISHADER_HPP

#include <GL/glew.h>

class IShader {
public:
	IShader(const char* vshader_path,const char* fshader_path);
	virtual ~IShader() { glDeleteProgram(CompiledProgramID); }
	const char* const VShader;
	const char* const FShader;
	GLuint CompiledProgramID;
};

#endif