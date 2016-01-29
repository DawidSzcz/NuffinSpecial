#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <GL/glew.h>
#include <list>
#include "IDrawable.hpp"
#include "DrawableHexagon.hpp"

class Background : public IDrawable {
public:
	Background(const TranslationVertexShader* shader, GLfloat hex_radius);
	virtual void SetupBuffers();
	virtual void Draw() const;
	virtual void CleanupBuffers();
	virtual ~Background();
protected:
	std::list<DrawableHexagon> hexes;
	GLfloat hex_r;
};

#endif