#ifndef ESCAPE_LINE_HPP
#define ESCAPE_LINE_HPP

#include <GL/glew.h>
#include "ICollidable.hpp"
#include "IObservable.hpp"

class EscapeLine : public ICollidable, public IObservable {
public:
	virtual void SetPrimitives();
	virtual void OnCollision(ICollidable* other,Contact details);
};

#endif