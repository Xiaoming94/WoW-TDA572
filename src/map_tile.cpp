#include "map_tile.h"
#include "avancezlib.h"
#include <iostream>
#define MAP_OFFSET 64
MapTile::MapTile(int row, int col)
{
	SDL_Log("Tile Created");

	std::cout << "row :" << row << " col: " << col << "\n";
	this -> enabled = true;
	this -> verticalPosition   = MAP_OFFSET + row * SPRITE_SIDE;
	this -> horizontalPosition = MAP_OFFSET + col * SPRITE_SIDE;
	std::cout << "x: " << horizontalPosition <<
		" y: " << verticalPosition << "\n";
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

RenderComponent * createTileRenderer(MapTile * tile, AvancezLib * system, std::set<GameObject*> * game_objects)
{
	RenderComponent * tileRenderer = new RenderComponent();
	tileRenderer->Create(system, tile, game_objects, tile->getWallType().c_str());
	return tileRenderer;
}