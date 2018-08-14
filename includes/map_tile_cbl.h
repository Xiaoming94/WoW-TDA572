#ifndef MAP_TILE_CBL_H
#define MAP_TILE_CBL_H
#include "map_tile.h"

class TileCBL :
	public MapTile
{
public:
	TileCBL();
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif