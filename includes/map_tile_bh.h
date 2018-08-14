#include "map_tile.h"

class TileBH :
	public MapTile
{
public:
	TileBH();
	std::string getWallType();
	bool ** getBinaryWall();
};