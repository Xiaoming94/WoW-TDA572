#include "map_tile_up.h"
#include "SDL.h"

TileUp::TileUp(int row, int col) :
	MapTile(row, col)
{
	SDL_Log("MapTile Up");
}

std::string TileUp::getWallType()
{
	return TILE_UP;
}

bool ** TileUp::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			if (i < 2)
			{
				bwp[i][j] = true;
			}
		}
	}
	return bwp;
}