#ifndef ITRANSLATION_VERTEX_SHADER_DRAWABLE_HPP
#define ITRANSLATION_VERTEX_SHADER_DRAWABLE_HPP

#include "IDrawable.hpp"
#include "TranslationVertexShader.hpp"

class ITranslationVertexShaderDrawable : public IDrawable {
public:
	ITranslationVertexShaderDrawable(const TranslationVertexShader* shader)
	: sh(shader) {}
protected:
	const TranslationVertexShader* sh;
};

#endif