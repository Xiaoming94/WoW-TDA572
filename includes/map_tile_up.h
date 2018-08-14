#ifndef MAP_TILE_UP_H
#define MAP_TILE_UP_H
#include "map_tile.h"

class TileUp :
	public MapTile
{
public:
	TileUp(int row, int col);
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif