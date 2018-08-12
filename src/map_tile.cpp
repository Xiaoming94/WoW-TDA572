#include "map_tile.h"
#include "avancezlib.h"

MapTile::MapTile()
{
	SDL_Log("Tile Created");

	this -> enabled = true;
}

MapTile::~MapTile()
{
	SDL_Log("Tile Destroyed");
}

std::string MapTile::getWallType()
{
	return "Default Wall";
}