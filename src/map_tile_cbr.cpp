#include "map_tile_cbr.h"
#include "SDL.h"

TileCBR::TileCBR(int row, int col) :
	MapTile(row, col)
{
	SDL_Log("MapTile CBR");
}

std::string TileCBR::getWallType()
{
	return TILE_CBR;
}

bool ** TileCBR::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			if (j > SPRITE_SIDE - 3 || i > SPRITE_SIDE - 3)
			{
				bwp[i][j] = true;
			}
		}
	}
	return bwp;
}