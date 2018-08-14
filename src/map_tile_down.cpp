#include "map_tile_down.h"
#include "SDL.h"

TileDown::TileDown() :
	MapTile()
{
	SDL_Log("MapTile DOWN");
}

std::string TileDown::getWallType()
{
	return TILE_DOWN;
}

bool ** TileDown::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			if (i > SPRITE_SIDE - 3)
			{
				bwp[i][j] = true;
			}
		}
	}
	return bwp;
}