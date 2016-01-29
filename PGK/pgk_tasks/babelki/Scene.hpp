#ifndef SCENE_HPP
#define SCENE_HPP

#include <algorithm>
#include <vector>
#include "BasicHeader.hpp"
#include "IDrawable.hpp"
#include "PointLight.hpp"
#include "IScene.hpp"
#include "ICamera.hpp"

class Scene : public IScene {
public:
	virtual void RegisterActor(const IDrawable* d) {
		assert(std::find(drawables.begin(),drawables.end(),d) == drawables.end());
		drawables.push_back(d);
	}

	virtual void UnregisterActor(const IDrawable* d) {
		auto it = std::find(drawables.begin(),drawables.end(),d);
		assert(it != drawables.end());
    	drawables.erase(it);
	}

	virtual const std::vector<const IDrawable*>& GetDrawables() const {
		return drawables;
	}
	
	virtual void RegisterActor(const PointLight* l) {
		assert(std::find(point_lights.begin(),point_lights.end(),l) == point_lights.end());
		point_lights.push_back(l);
	}

	virtual void UnregisterActor(const PointLight* l) {
		auto it = std::find(point_lights.begin(),point_lights.end(),l);
		assert(it != point_lights.end());
    	point_lights.erase(it);
	}

	virtual const std::vector<const PointLight*>& GetPointLights() const {
		return point_lights;
	}

protected:
	std::vector<const IDrawable*> drawables;
	std::vector<const PointLight*> point_lights;
};

#endif