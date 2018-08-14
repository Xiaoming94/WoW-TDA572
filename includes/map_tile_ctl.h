#ifndef MAP_TILE_CTL_H
#define MAP_TILE_CTL_H
#include "map_tile.h"

class TileCTL :
	public MapTile
{
public:
	TileCTL();
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif