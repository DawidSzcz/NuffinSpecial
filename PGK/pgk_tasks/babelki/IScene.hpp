#ifndef ISCENE_HPP
#define ISCENE_HPP

#include <vector>
#include "BasicHeader.hpp"
#include "IDrawable.hpp"
#include "PointLight.hpp"
#include "ICamera.hpp"

class IScene {
public:
	virtual void RegisterActor(const IDrawable* d) = 0;
	virtual void UnregisterActor(const IDrawable* d) = 0;
	virtual const std::vector<const IDrawable*>& GetDrawables() const = 0;

	virtual void RegisterActor(const PointLight* l) = 0;
	virtual void UnregisterActor(const PointLight* l) = 0;
	virtual const std::vector<const PointLight*>& GetPointLights() const = 0;
	
	const ICamera* Camera;

	IScene() { Camera = NULL; }

	virtual ~IScene() {};
};

#endif