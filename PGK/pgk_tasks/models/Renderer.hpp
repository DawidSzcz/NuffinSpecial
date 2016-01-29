#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "types.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

class Renderer {
public:
	virtual void Render(Scene& scene,Camera& camera) const;
};

#endif