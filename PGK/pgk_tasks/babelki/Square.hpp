#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "BasicHeader.hpp"
#include "IDrawable.hpp"

class Square : public IDrawable {
public:
	Square(Coord_t width,Coord_t height,Colour_t colour)
	: Width(width), Height(height), Colour(colour) {
		Model = glm::scale(Transformation_t(1.0),Position_t(Width,Height,1.0));
	}

	virtual unsigned long int GetVerticesNum() const { return 4; }
	virtual unsigned long int GetTrianglesNum() const { return 2; }
	const Coord_t Width;
	const Coord_t Height;
	const Colour_t Colour;

	virtual void GenVertices(std::vector<Vertex_t>& vertices,std::vector<TrIndex_t>& triangles) const {
		unsigned long int start = vertices.size();
		vertices.push_back(Vertex_t(Position_t(0.0,0.0,0.0),Colour,Position_t(0.0,0.0,1.0)));
		vertices.push_back(Vertex_t(Position_t(1.0,0.0,0.0),Colour,Position_t(0.0,0.0,1.0)));
		vertices.push_back(Vertex_t(Position_t(1.0,1.0,0.0),Colour,Position_t(0.0,0.0,1.0)));
		vertices.push_back(Vertex_t(Position_t(0.0,1.0,0.0),Colour,Position_t(0.0,0.0,1.0)));
		
		triangles.push_back(TrIndex_t(	start,
										start+1,
										start+3));
		triangles.push_back(TrIndex_t(	start+1,
										start+2,
										start+3));
	}
protected:
};

#endif