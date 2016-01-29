#ifndef ISHADER_HPP
#define ISHADER_HPP

#include <string>
#include "common/shader.hpp"
#include "BasicHeader.hpp"
#include "IDrawable.hpp"
#include "PointLight.hpp"
#include "ICamera.hpp"

class IShader {
public:
	virtual void SetUniforms(const IDrawable& d,const ICamera* camera,const std::vector<const PointLight*>& lights) = 0;
	virtual void OnBind() = 0;
	virtual void OnUnbind() = 0;
	virtual void OnArrayBufferBind() = 0;

	virtual GLuint GetID() const { return id; } 
	const std::string VShaderPath;
	const std::string PShaderPath;
	
	IShader(const std::string vshader,const std::string pshader)
	: VShaderPath(vshader), PShaderPath(pshader) {
		id = LoadShaders(VShaderPath.c_str(),PShaderPath.c_str());
	}
	
	virtual ~IShader() { glDeleteProgram(id); }
protected:
	GLuint id;
};

#endif