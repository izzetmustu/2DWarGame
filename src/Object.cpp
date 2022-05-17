#include "Object.h"

//draws image to buffer, common for all subclasses
void Object::paint() {
	window->draw(sprite);
}

Object::~Object() { }