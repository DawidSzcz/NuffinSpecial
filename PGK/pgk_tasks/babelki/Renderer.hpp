#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "BasicHeader.hpp"
#include "IDrawable.hpp"
#include "PointLight.hpp"
#include "GPUManager.hpp"
#include "IScene.hpp"
#include "ICamera.hpp"

class Renderer {
public:
	virtual void Draw(const IDrawable& d,const ICamera* camera,const std::vector<const PointLight*>& lights) {
		GPU->BindProgram(d.Shader);
		GPU->BindArrayBuffer(d.VertexBufferID);
		GPU->BindElementArrayBuffer(d.IndexBufferID);
		GPU->SetUniforms(d,camera,lights);
		GPU->DrawTriangles(d.GetTrianglesNum(),d.IndexBufferOffset);
	}

	virtual void Draw(const IScene& s) {
		GPU->ClearBuffers();
		for(auto ptr : s.GetDrawables()) Draw(*ptr,s.Camera,s.GetPointLights());
	}

	//madry management bufforami

	Renderer(GPUManager* gpu)
	: GPU(gpu) {}

	virtual ~Renderer() {}
protected:
	GPUManager* GPU;
};

#endif