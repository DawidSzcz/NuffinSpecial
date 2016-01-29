#include <utility>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "DrawableHexagonExterior.hpp"
#include "ICollidable.hpp"
#include "Borders.hpp"

#include <iostream>

Borders::Borders(	const TranslationVertexShader* shader,
					GLfloat radius,
					GLfloat colorR, GLfloat colorG, GLfloat colorB,
					GLfloat border_width,
					GLfloat borderColorR, GLfloat borderColorG, GLfloat borderColorB
)
: DrawableHexagonExterior(shader,radius,colorR,colorG,colorB,border_width,borderColorR,borderColorG,borderColorB) {}

void Borders::SetPrimitives() {
	GLfloat s = glm::sin(M_PI/3.0);
	GLfloat c = glm::cos(M_PI/3.0);	

	CollisionPrimitive prim(CollisionPrimitive::HALFPLANE);
	// top
	prim.norm = glm::vec3(0.0,-1.0,0.0);
	Primitives.push_back(std::make_pair(prim,glm::vec3(0.0,s*r,0.0)));
	// top-left
	prim.norm = glm::normalize(glm::vec3(s,-c,0.0));
	Primitives.push_back(std::make_pair(prim,glm::vec3(-r,0.0,0.0)));
	// bottom-right
	prim.norm = -prim.norm;
	Primitives.push_back(std::make_pair(prim,glm::vec3(r,0.0,0.0)));
	// top-right
	prim.norm = glm::normalize(glm::vec3(-s,-c,0.0));
	Primitives.push_back(std::make_pair(prim,glm::vec3(r,0.0,0.0)));
	// bottom-left
	prim.norm = -prim.norm;
	Primitives.push_back(std::make_pair(prim,glm::vec3(-r,0.0,0.0)));
}

void Borders::OnCollision(ICollidable* /*other*/,Contact /*details*/) {
	std::cerr<< "Borders collision\n";
}