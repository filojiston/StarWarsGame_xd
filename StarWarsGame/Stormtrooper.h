#pragma once

#include <queue>
#include <vector>
#include <iostream>
#include "Character.h"


class Stormtrooper :
	public Character
{
public:
	Stormtrooper();
	std::vector<Location> findShortestPath(Location source, Location destination);
};