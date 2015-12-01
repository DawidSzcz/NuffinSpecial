#ifndef BRICK_HPP
#define BRICK_HPP

#include <GL/glew.h>
#include "PersistentBrick.hpp"

class Brick : public PersistentBrick {
public:
	Brick(	const TranslationVertexShader* shader,
			GLfloat width=0.07, GLfloat height=0.07,
			GLfloat colorR=1.0, GLfloat colorG=0.0, GLfloat colorB=0.0,
			GLfloat border_width=0.005,
			GLfloat borderColorR=0.1, GLfloat borderColorG=0.0, GLfloat borderColorB=0.3
	);
	virtual void Activate();
	virtual void Deactivate();
	virtual void Draw() const;
	virtual void SetPrimitives();
	virtual void OnCollision(ICollidable* other,Contact details);
	virtual void NotifyObservers(Notification n) const;
protected:
	bool isActive;
};

#endif