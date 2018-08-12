#include "game_map.h"
#include "map_tile_bh.h"
#include <sstream>
#include <iostream>

MapTile * buildMapTile(std::string tileToken) {
	if (!tileToken.compare("bh"))
	{
		return new TileBH();
	}
	else
	{
		return new MapTile();
	}
}

GameMap::GameMap(
	std::string mapString,
	int width,
	int height
)
{
	this -> width  = width;
	this -> height = height;
	std::istringstream mss = std::istringstream(mapString);
	std::string line;
	while (std::getline(mss, line, '\n'))
	{
		SDL_Log(line.c_str());
		std::istringstream tilestring = std::istringstream(line);
		std::string tileToken;
		while (std::getline(tilestring, tileToken, ','))
		{
			tiles.push_back(buildMapTile(tileToken));
		}
	}
}


GameMap::~GameMap()
{
}

GameMap CreateStandardMap()
{
	std::string standardMap =
		"ctl,bh,ctr\nleft,bh,right\ncbl,bh,cbr";

	return GameMap(standardMap, 3, 3);
}