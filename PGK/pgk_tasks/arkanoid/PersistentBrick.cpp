#include <list>
#include <utility>
#include <glm/glm.hpp>
#include "ICollidable.hpp"
#include "DrawableRectangle.hpp"
#include "PersistentBrick.hpp"

#include <iostream>

PersistentBrick::PersistentBrick(	const TranslationVertexShader* shader,
									GLfloat width, GLfloat height,
									GLfloat colorR, GLfloat colorG, GLfloat colorB,
									GLfloat border_width,
									GLfloat borderColorR, GLfloat borderColorG, GLfloat borderColorB
)
: DrawableRectangle(shader,width,height,colorR,colorG,colorB,border_width,borderColorR,borderColorG,borderColorB) {}

void PersistentBrick::SetPrimitives() {
	CollisionPrimitive prim(CollisionPrimitive::CIRCLE);
	prim.r = std::min(w,h)*0.5;
	Primitives.push_back(std::make_pair(prim,glm::vec3(0.0)));	
}

void PersistentBrick::OnCollision(ICollidable* /*other*/,Contact /*details*/) {
	std::cerr << "PersistentBrick collision\n";
}