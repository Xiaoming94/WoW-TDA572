#include "map_tile_ctr.h"
#include "SDL.h"

TileCTR::TileCTR() :
	MapTile()
{
	SDL_Log("MapTile CTR");
}

std::string TileCTR::getWallType()
{
	return TILE_CTR;
}

bool ** TileCTR::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			if (i < 2 || j > SPRITE_SIDE - 3)
			{
				bwp[i][j] = true;
			}
		}
	}
	return bwp;
}