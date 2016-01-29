#ifndef CARD_HPP
#define CARD_HPP

#include <GL/glew.h>

class Card {
public:
	static const int VerticesNum = 6;
	static const int CoordsSize = VerticesNum*3;
	static const int CardColorSize = 3;
	
	Card(int ID);
	virtual int GetId() const;
	GLfloat Coords[CoordsSize];
	GLfloat BackColor[CardColorSize];
	GLfloat FaceColor[CardColorSize];
	virtual ~Card() {}
protected:
	int id;
};

#endif