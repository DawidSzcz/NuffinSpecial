#include "Card.hpp"

Card::Card(int ID)
: id(ID) {}

int Card::GetId() const {
	return id;
}