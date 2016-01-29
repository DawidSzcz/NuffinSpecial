#ifndef DRAWING_MANAGER_HPP
#define DRAWING_MANAGER_HPP

#include <list>
#include <GL/glew.h>
#include "IDrawable.hpp"

class DrawingManager {
public:
	DrawingManager() { glClearColor(bgR,bgG,bgB,0.0); }
	virtual void Register(const IDrawable* x) { if(x != NULL) objects.push_back(x); }
	virtual void DrawAll();
	virtual ~DrawingManager() { objects.clear(); }
protected:
	GLfloat bgR=0.15, bgG=0.02, bgB=0.5;
	std::list<const IDrawable*> objects;
};

#endif