#include "map_tile_cbl.h"
#include "SDL.h"

TileCBL::TileCBL() :
	MapTile()
{
	SDL_Log("MapTile CBL");
}

std::string TileCBL::getWallType()
{
	return TILE_CBL;
}

bool ** TileCBL::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			if (j < 2 || i > SPRITE_SIDE - 3)
			{
				bwp[i][j] = true;
			}
		}
	}
	return bwp;
}