#include "map_tile.h"

class TileBH :
	public MapTile
{
public:
	TileBH(int row, int col);
	std::string getWallType();
	bool ** getBinaryWall();
};