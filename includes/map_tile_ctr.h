#ifndef MAP_TILE_CTR_H
#define MAP_TILE_CTR_H
#include "map_tile.h"

class TileCTR :
	public MapTile
{
public:
	TileCTR();
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif