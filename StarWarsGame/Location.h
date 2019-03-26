#pragma once
class Location
{
public:
	Location() {}
	Location(int x, int y) { this->x = x;  this->y = y; }
public:
	// getters
	int getX() { return x; }
	int getY() { return y; }

	// setters
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
private:
	int x;		// x coordinate
	int y;		// y coordinate
};