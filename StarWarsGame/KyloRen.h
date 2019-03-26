#pragma once

#include <queue>
#include <vector>
#include <iostream>

#include "Character.h"
class KyloRen :
	public Character
{
public:
	KyloRen();
	std::vector<Location> findShortestPath(Location source, Location destination);
};