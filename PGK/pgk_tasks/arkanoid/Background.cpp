#include <GL/glew.h>
#include <glm/glm.hpp>
#include <list>
#include "IDrawable.hpp"
#include "DrawableHexagon.hpp"
#include "Background.hpp"

Background::Background(const TranslationVertexShader* shader, GLfloat hex_radius)
: hex_r(hex_radius) {
	DrawableHexagon h(shader,hex_r,0.15,0.02,0.5,hex_r*0.13,0.1,0.01,0.32);
	
	bool even = true;

	for(GLfloat x = 0.0 ; x < 1.0+hex_r ; x += glm::cos(M_PI/6.0)*(hex_r+hex_r)) {
		GLfloat offset = (even ? 0.0 : hex_r);

		for(GLfloat y = 0.0 ; y < 1.0+hex_r+offset ; y += hex_r+hex_r) {
			h.Position = glm::vec3(x,y+offset,0.0);
			hexes.push_back(h);
			h.Position = glm::vec3(x,-y+offset,0.0);
			hexes.push_back(h);
			h.Position = glm::vec3(-x,y+offset,0.0);
			hexes.push_back(h);
			h.Position = glm::vec3(-x,-y+offset,0.0);
			hexes.push_back(h);
		}
		even = !even;
	}
}

void Background::SetupBuffers() {
	for(auto it = hexes.begin() ; it != hexes.end() ; it++)
		it->SetupBuffers();
}

void Background::Draw() const {
	for(auto it = hexes.begin() ; it != hexes.end() ; it++)
		it->Draw();
}

void Background::CleanupBuffers() {
	for(auto it = hexes.begin() ; it != hexes.end() ; it++)
		it->CleanupBuffers();
}

Background::~Background() {
	hexes.clear();
}