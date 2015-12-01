#include "IMovable.hpp"
#include "MotionManager.hpp"

void MotionManager::HandleFrameMotion(double delta_sec) {
	for(auto it = objects.begin(); it != objects.end() ; it++)
		(*it)->UpdateState(delta_sec);
}