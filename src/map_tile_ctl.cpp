#include "map_tile_ctl.h"
#include "SDL.h"

TileCTL::TileCTL(int row, int col) :
	MapTile(row, col)
{
	SDL_Log("MapTile CTL");
}

std::string TileCTL::getWallType()
{
	return TILE_CTL;
}

bool ** TileCTL::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			if (i < 2 || j < 2)
			{
				bwp[i][j] = true;
			}
		}
	}
	return bwp;
}