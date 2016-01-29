#include <GL/glew.h>
#include "IDrawable.hpp"
#include "DrawingManager.hpp"

void DrawingManager::DrawAll() {
	glClear(GL_COLOR_BUFFER_BIT);

	for(auto it = objects.begin(); it != objects.end() ; it++)
		(*it)->Draw();
}