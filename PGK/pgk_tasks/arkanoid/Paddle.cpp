#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ICollidable.hpp"
#include "DrawableCircularSegment.hpp"
#include "Paddle.hpp"
#include "Borders.hpp"

Paddle::Paddle(	const TranslationVertexShader* shader,
				GLfloat radius, GLfloat central_angle,
				GLfloat colorR, GLfloat colorG, GLfloat colorB,
				GLfloat border_width,
				GLfloat borderColorR, GLfloat borderColorG, GLfloat borderColorB
)
: DrawableCircularSegment(shader,radius,central_angle,colorR,colorG,colorB,border_width,borderColorR,borderColorG,borderColorB) {}

void Paddle::SetPrimitives() {
	CollisionPrimitive prim(CollisionPrimitive::CIRCLE);
	prim.r = r;
	Primitives.push_back(std::make_pair(prim,circle_center_pos));
}

void Paddle::OnCollision(ICollidable* other,Contact details) {
	std::cerr << "Paddle collision\n";

	if(dynamic_cast<Borders*>(other) != NULL) {
		Position[0] += (details.penetration/glm::sin(M_PI/3.0))*((details.norm[0] < 0.0) ? -1.0 : 1.0);
	}

}