#include "map_tile_bv.h"
#include "SDL.h"

TileBV::TileBV(int row, int col) :
	MapTile(row, col)
{
	SDL_Log("MapTile BV");
}

std::string TileBV::getWallType()
{
	return TILE_BV;
}

bool ** TileBV::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			if (i < 2 || i > SPRITE_SIDE - 3)
			{
				bwp[i][j] = true;
			}
		}
	}
	return bwp;
}