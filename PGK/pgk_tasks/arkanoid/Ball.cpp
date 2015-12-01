#include <list>
#include <utility>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ICollidable.hpp"
#include "DrawableCircle.hpp"
#include "Ball.hpp"

#include <iostream>

Ball::Ball(	const TranslationVertexShader* shader,
			GLfloat radius,
			GLfloat colorR, GLfloat colorG, GLfloat colorB,
			GLfloat border_width,
			GLfloat borderColorR, GLfloat borderColorG, GLfloat borderColorB
)
: DrawableCircle(shader,radius,colorR,colorG,colorB,border_width,borderColorR,borderColorG,borderColorB) {}

void Ball::SetPrimitives() {
	CollisionPrimitive prim(CollisionPrimitive::CIRCLE);
	prim.r = r;
	Primitives.push_back(std::make_pair(prim,glm::vec3(0.0)));
}

void Ball::OnCollision(ICollidable* /*other*/,Contact details) {
std::cerr<< "Ball collision\n";
	Position += details.penetration*details.norm;
	Velocity = glm::reflect(Velocity,details.norm);
}