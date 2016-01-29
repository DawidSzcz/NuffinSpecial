#ifndef MOTION_MANAGER_HPP
#define MOTION_MANAGER_HPP

#include <list>
#include "IMovable.hpp"

class MotionManager {
public:
	virtual void Register(IMovable* x) { if(x != NULL) objects.push_back(x); }
	virtual void HandleFrameMotion(double delta_sec);
	virtual ~MotionManager() { objects.clear(); }
protected:
	std::list<IMovable*> objects;
};

#endif