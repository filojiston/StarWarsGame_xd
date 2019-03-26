#include "Map.h"

int **Map::map;

Map::Map()
{
	initMap();
	readMap();
}

void Map::initMap()
{
	map = new int*[14];
	for (int i = 0; i < MAPX; i++)
		map[i] = new int[MAPY];

	for (int i = 0; i < MAPY; i++)
		for (int j = 0; j < MAPX; j++)
			map[j][i] = 0;
}

void Map::readMap()
{
	std::string line;

	int x = 0;
	int y = 0;

	std::ifstream inputText("Harita.txt");
	if (inputText.is_open())
	{
		while (std::getline(inputText, line))
		{
			if (line.find("Karakter") != std::string::npos)
			{
				continue;
			}
			else
			{
				int lineLen = line.length();
				char temp;

				for (int i = 0; i < lineLen; i++)
				{
					temp = line[i];

					if (temp != '\t')
					{
						map[x][y] = temp - '0';
						x++;
					}
				}
				x = 0;
				y++;
			}
		}
	}
	inputText.close();
}