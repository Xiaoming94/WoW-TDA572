#ifndef MAP_TILE_LEFT_H
#define MAP_TILE_LEFT_H
#include "map_tile.h"

class TileLeft :
	public MapTile
{
public:
	TileLeft(int row,int col);
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif