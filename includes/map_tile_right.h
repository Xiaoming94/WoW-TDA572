#ifndef MAP_TILE_RIGHT_H
#define MAP_TILE_RIGHT_H
#include "map_tile.h"

class TileRight :
	public MapTile
{
public:
	TileRight(int row, int col);
	std::string getWallType();
	bool ** getBinaryWall();
};

#endif