#include <list>
#include <utility>
#include <GL/glew.h>
#include "ICollidable.hpp"
#include "IObservable.hpp"
#include "Ball.hpp"
#include "EscapeLine.hpp"

#include <iostream>

void EscapeLine::SetPrimitives() {
	CollisionPrimitive prim(CollisionPrimitive::HALFPLANE);
	prim.norm = glm::vec3(0.0,1.0,0.0);
	Primitives.push_back(std::make_pair(prim,glm::vec3(0.0)));
}

void EscapeLine::OnCollision(ICollidable* other,Contact /*details*/) {
	std::cerr << "EscapeLine collision\n";
	
	if(dynamic_cast<Ball*>(other) != NULL)
		NotifyObservers(Notification(Notification::BALL_ESCAPE));
}