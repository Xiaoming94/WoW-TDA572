#ifndef MAP_TILE_CBL_H
#define MAP_TILE_CBL_H
#include "map_tile.h"

class TileCBL :
	public MapTile
{
public:
	TileCBL(int row, int col);
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif