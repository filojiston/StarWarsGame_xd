#include "DarthVader.h"



DarthVader::DarthVader()
{
	setName("Darth Vader");
	setType("Evil");
}

std::vector<Location> DarthVader::findShortestPath(Location source, Location destination)
{
	std::vector<Location> shortestPath;

	int **map = Map::getMap();
	bool visited[Map::MAPX][Map::MAPY];

	for (int i = 0; i < Map::MAPY; i++)
		for (int j = 0; j < Map::MAPX; j++)
			visited[j][i] = false;

	std::queue<Node> q;
	Node src;
	src.loc = source;
	src.distance = 0;
	q.push(src);
	visited[source.getX()][source.getY()] = true;
	shortestPath.push_back(source);
	src.path = shortestPath;

	while (!q.empty())
	{
		Node loc = q.front();
		q.pop();

		if (loc.loc.getX() == destination.getX() && loc.loc.getY() == destination.getY())
		{
			this->setDistance(loc.distance);
			return loc.path;
		}

		if (loc.loc.getX() - 1 >= 0 && !visited[loc.loc.getX() - 1][loc.loc.getY()])
		{
			Node n;
			n.distance = loc.distance + 1;
			n.loc = Location(loc.loc.getX() - 1, loc.loc.getY());
			std::vector<Location> path(loc.path);
			path.push_back(loc.loc);
			n.path = path;
			q.push(n);
			visited[loc.loc.getX() - 1][loc.loc.getY()] = true;
		}

		if (loc.loc.getX() + 1 < Map::MAPX && !visited[loc.loc.getX() + 1][loc.loc.getY()])
		{
			Node n;
			n.distance = loc.distance + 1;
			n.loc = Location(loc.loc.getX() + 1, loc.loc.getY());
			std::vector<Location> path(loc.path);
			path.push_back(loc.loc);
			n.path = path;
			q.push(n);
			visited[loc.loc.getX() + 1][loc.loc.getY()] = true;
		}

		if (loc.loc.getY() - 1 >= 0 && !visited[loc.loc.getX()][loc.loc.getY() - 1])
		{
			Node n;
			n.distance = loc.distance + 1;
			n.loc = Location(loc.loc.getX(), loc.loc.getY() - 1);
			std::vector<Location> path(loc.path);
			path.push_back(loc.loc);
			n.path = path;
			q.push(n);
			visited[loc.loc.getX()][loc.loc.getY() - 1] = true;
		}

		if (loc.loc.getY() + 1 < Map::MAPY && !visited[loc.loc.getX()][loc.loc.getY() + 1])
		{
			Node n;
			n.distance = loc.distance + 1;
			n.loc = Location(loc.loc.getX(), loc.loc.getY() + 1);
			std::vector<Location> path(loc.path);
			path.push_back(loc.loc);
			n.path = path;
			q.push(n);
			visited[loc.loc.getX()][loc.loc.getY() + 1] = true;
		}
	}
	return shortestPath;
}