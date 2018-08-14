#ifndef MAP_TILE_BV_H
#define MAP_TILE_BV_H
#include "map_tile.h"

class TileBV :
	public MapTile
{
public:
	TileBV(int row, int col);
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif