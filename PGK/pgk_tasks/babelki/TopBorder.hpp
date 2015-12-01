#ifndef TOP_BORDER_HPP
#define TOP_BORDER_HPP

#include "BasicHeader.hpp"
#include "Border.hpp"

class TopBorder : public Border {
public:
	TopBorder(Transformation_t modelMatrix,Coord_t width,Coord_t height,Colour_t c)
	: Border(modelMatrix,width,height,c) {}
};

#endif