#include "map_tile.h"
#include "avancezlib.h"
#include <iostream>

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

void printBinaryMap(MapTile tile)
{
	std::cout << "[\n";
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			std::cout << tile.bwp[i][j] <<" ";
		}
		std::cout << "\n";
	}
	std::cout << "]\n";

}