#pragma once

#include <string>
#include <vector>

#include "Location.h"
#include "Map.h"

class Character
{
public:
	Character() {}
public:
	// getters
	std::string getName() { return name; }
	std::string getType() { return type; }
	Location	getLocation() { return currentLocation; }
	Location	getStartLocation() { return startLocation; }
	int			getDistance() { return distance; }

	// setters
	void		setName(std::string name) { this->name = name; }
	void		setType(std::string type) { this->type = type; }
	void		setLocation(Location location) { this->currentLocation = location; }
	void		setLocation(int x, int y) { currentLocation.setX(x);	currentLocation.setY(y); }
	void		setStartLocation(Location loc) { this->startLocation = loc; }
	void		setStartLocation(int x, int y) { startLocation.setX(x);	startLocation.setY(y); }
	void		setDistance(int distance) { this->distance = distance; }
	virtual std::vector<Location> findShortestPath(Location source, Location destinaton) { return std::vector<Location>(); }
protected:
	struct Node
	{
		Location loc;
		int distance;
		std::vector<Location> path;
	};
private:
	std::string name;			// character's name
	std::string type;			// character's type (good / bad)
	Location currentLocation;	// character's current location at map
	Location startLocation;		// character's start location (used at reset method)
	int distance;
};