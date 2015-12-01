#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

struct Contact {
	bool isContact;
	glm::vec3 norm;
	GLfloat penetration;

	static Contact Reverse(Contact c) { c.norm = -c.norm; return c; }
	Contact(bool isC,glm::vec3 n=glm::vec3(0.0), GLfloat p=0.0)
	: isContact(isC), norm(n), penetration(p) {}
};

#endif