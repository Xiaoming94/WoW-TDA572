#ifndef MAP_TILE_CBR_H
#define MAP_TILE_CBR_H
#include "map_tile.h"

class TileCBR :
	public MapTile
{
public:
	TileCBR();
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif