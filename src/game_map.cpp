#include "game_map.h"
#include <sstream>
#include <iostream>

MapTile * buildMapTile(std::string tileToken) {
	if (!tileToken.compare("bh"))
	{
		return new TileBH();
	}
	if (!tileToken.compare("bv"))
	{
		return new TileBV();
	}
	if (!tileToken.compare("ctl"))
	{
		return new TileCTL();
	}
	if (!tileToken.compare("ctr"))
	{
		return new TileCTR();
	}
	if (!tileToken.compare("cbl"))
	{
		return new TileCBL();
	}
	if (!tileToken.compare("cbr"))
	{
		return new TileCBR();
	}
	if (!tileToken.compare("up"))
	{
		return new TileUp();
	}
	if (!tileToken.compare("left"))
	{
		return new TileLeft();
	}
	if (!tileToken.compare("right"))
	{
		return new TileRight();
	}
	if (!tileToken.compare("down"))
	{
		return new TileDown();
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
		std::istringstream tilestring = std::istringstream(line);
		std::string tileToken;
		while (std::getline(tilestring, tileToken, ','))
		{
			MapTile * tile = buildMapTile(tileToken);
			printBinaryMap(tile);
			tiles.push_back(tile);
		}
	}
}


GameMap::~GameMap()
{
}

GameMap CreateStandardMap()
{
	std::string standardMap =
		"bh,bv,cbl,cbr,ctl,ctr,down,left,right,up\n";

	return GameMap(standardMap, 10,1);
}