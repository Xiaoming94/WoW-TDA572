#include "game_map.h"
#include <sstream>
#include <iostream>

MapTile * buildMapTile(std::string tileToken, int row, int col) {
	if (!tileToken.compare("bh"))
	{
		return new TileBH(row,col);
	}
	if (!tileToken.compare("bv"))
	{
		return new TileBV(row,col);
	}
	if (!tileToken.compare("ctl"))
	{
		return new TileCTL(row,col);
	}
	if (!tileToken.compare("ctr"))
	{
		return new TileCTR(row,col);
	}
	if (!tileToken.compare("cbl"))
	{
		return new TileCBL(row,col);
	}
	if (!tileToken.compare("cbr"))
	{
		return new TileCBR(row,col);
	}
	if (!tileToken.compare("u"))
	{
		return new TileUp(row,col);
	}
	if (!tileToken.compare("l"))
	{
		return new TileLeft(row,col);
	}
	if (!tileToken.compare("r"))
	{
		return new TileRight(row,col);
	}
	if (!tileToken.compare("d"))
	{
		return new TileDown(row,col);
	}
	else
	{
		return new MapTile(row,col);
	}
}

GameMap::GameMap(
	std::string mapString,
	int width,
	int height,
	AvancezLib * system,
	std::set<GameObject*> * game_objects
)
{
	this -> width  = width;
	this -> height = height;
	std::istringstream mss = std::istringstream(mapString);
	std::string line;
	int row = 0;
	while (std::getline(mss, line, '\n'))
	{
		std::istringstream tilestring = std::istringstream(line);
		std::string tileToken;
		int col = 0;
		while (std::getline(tilestring, tileToken, ','))
		{
			MapTile * tile = buildMapTile(tileToken,row,col);
			tiles.push_back(tile);
			col++;
		}
		row++;
	}
	for (MapTile * tile : tiles)
	{
		RenderComponent * tileRenderer = createTileRenderer(tile, system, game_objects);
		tile -> AddComponent(tileRenderer);
	}
}


GameMap::~GameMap()
{
	//To be implemented
}

void GameMap::renderMap(float dt)
{
	for (MapTile * tile : tiles)
	{
		tile -> Update(dt);
	}
}

GameMap * CreateStandardMap(
	AvancezLib * system,
	std::set <GameObject*> * game_objects	
)
{
	std::string standardMap = "ctl,bv,bv,u,u,u,bv,bv,ctr\n";
	standardMap = standardMap + "bh,ctl,bv,bh,bh,bh,bv,ctr,bh\n";
	standardMap = standardMap + "bh,cbl,bv,r,bh,l,bv,cbr,bh\n";
	standardMap = standardMap + "l,bv,bv,e,e,e,bv,bv,r\n";
	standardMap = standardMap + "bh,ctl,bv,r,bh,l,bv,ctr,bh\n";
	standardMap = standardMap + "bh,cbl,bv,bh,bh,bh,bv,cbr,bh\n";
	standardMap = standardMap + "cbl,bv,bv,d,d,d,bv,bv,cbr";

	return new GameMap(standardMap, 3,3, system, game_objects);
}