#pragma once
class Coord {
public:
	float x;
	float y;
public:
	Coord() : x(0.0), y(0.0) {}				//default constructor
	Coord(float x, float y): x(x), y(y) {}	//non default constructor
	Coord(const Coord&);
	Coord& operator=(const Coord&);
};

