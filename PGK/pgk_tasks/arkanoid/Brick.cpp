#include <list>
#include <GL/glew.h>
#include "PersistentBrick.hpp"
#include "Brick.hpp"

#include <iostream>

Brick::Brick(	const TranslationVertexShader* shader,
				GLfloat width, GLfloat height,
				GLfloat colorR, GLfloat colorG, GLfloat colorB,
				GLfloat border_width,
				GLfloat borderColorR, GLfloat borderColorG, GLfloat borderColorB
)
: PersistentBrick(shader,width,height,colorR,colorG,colorB,border_width,borderColorR,borderColorG,borderColorB), isActive(true) {}

void Brick::Activate() {
	isActive = true;
	SetPrimitives();
}

void Brick::Deactivate() {
	isActive = false;
	SetPrimitives();
}

void Brick::Draw() const {
	if(isActive) PersistentBrick::Draw();
}

void Brick::SetPrimitives() {
	if(isActive) PersistentBrick::SetPrimitives();
	else Primitives.clear();
}

void Brick::OnCollision(ICollidable* /*other*/,Contact /*details*/) {
	std::cerr << "Brick collision\n";
	NotifyObservers(Notification(Notification::BRICK_HIT));
	Deactivate();
}

void Brick::NotifyObservers(Notification n) const {
	if(isActive) PersistentBrick::NotifyObservers(n);
}