#pragma once

#include <queue>
#include <vector>
#include <iostream>

#include "Character.h"
class DarthVader :
	public Character
{
public:
	DarthVader();
	std::vector<Location> findShortestPath(Location source, Location destination);
};