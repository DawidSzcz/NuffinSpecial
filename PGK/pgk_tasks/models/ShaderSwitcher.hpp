#ifndef SHADER_SWITCHER_HPP
#define SHADER_SWITCHER_HPP

#include "types.hpp"
#include <vector>

class ShaderSwitcher {
public:
	void GetControls();
	std::vector<GLuint> Shaders;
	unsigned int current=0;
};

#endif