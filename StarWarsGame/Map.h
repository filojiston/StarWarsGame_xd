#pragma once

#include <fstream>
#include <string>

class Map
{
public:
	Map();
public:
	void initMap();
	static int** getMap() { return map; }
private:
	static int **map;
public:
	const static int MAPX = 14;
	const static int MAPY = 11;
private:
	void readMap();
};