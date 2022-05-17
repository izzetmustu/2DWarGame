#include "Coord.h"

Coord::Coord(const Coord& c) {
	this->x = c.x;
	this->y = c.y;
}

Coord& Coord::operator=(const Coord& c) {
	this->x = c.x;
	this->y = c.y;
	return *this;
}

