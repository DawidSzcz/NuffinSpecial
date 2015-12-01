#ifndef MONOCHROMATIC_SPHERE_HPP
#define MONOCHROMATIC_SPHERE_HPP

#include "BasicHeader.hpp"
#include "IDrawable.hpp"

class MonochromaticSphere : public IDrawable {
public:
	MonochromaticSphere(Colour_t colour)
	: Colour(colour) {
		Model = Transformation_t(1.0);
	}

	virtual unsigned long int GetVerticesNum() const { return 2 + longitudes*(latitudes-1); }
	virtual unsigned long int GetTrianglesNum() const { return 2*longitudes*(latitudes-1); }
	const Colour_t Colour;

	virtual void GenVertices(std::vector<Vertex_t>& vertices,std::vector<TrIndex_t>& triangles) const;
protected:
	const unsigned long int latitudes = 32;
	const unsigned long int longitudes = 64;
};

#endif