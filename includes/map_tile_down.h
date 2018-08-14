#ifndef MAP_TILE_DOWN_H
#define MAP_TILE_DOWN_H
#include "map_tile.h"

class TileDown :
	public MapTile
{
public:
	TileDown(int row, int col);
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif