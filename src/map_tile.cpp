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

bool ** MapTile::getBinaryWall()
{
	bool ** bwp = new bool*[SPRITE_SIDE];
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		bwp[i] = new bool[SPRITE_SIDE];
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			bwp[i][j] = false;
		}
	}
	return bwp;
}

void printBinaryMap(MapTile * tile)
{
	bool ** bwp = tile -> getBinaryWall();
	std::cout << "[\n";
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			std::cout << bwp[i][j] <<" ";
		}
		std::cout << "\n";
	}
	std::cout << "]\n";

}
