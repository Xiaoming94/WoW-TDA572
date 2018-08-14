#include "map_tile_left.h"
#include "SDL.h"

TileLeft::TileLeft() :
	MapTile()
{
	SDL_Log("MapTile LEFT");
}

std::string TileLeft::getWallType()
{
	return TILE_LEFT;
}

bool ** TileLeft::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			if (j < 2)
			{
				bwp[i][j] = true;
			}
		}
	}
	return bwp;
}