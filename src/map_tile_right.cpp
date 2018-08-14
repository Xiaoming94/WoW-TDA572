#include "map_tile_right.h"
#include "SDL.h"

TileRight::TileRight(int row, int col) :
	MapTile(row, col)
{
	SDL_Log("MapTile RIGHT");
}

std::string TileRight::getWallType()
{
	return TILE_RIGHT;
}

bool ** TileRight::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			if (j > SPRITE_SIDE - 3)
			{
				bwp[i][j] = true;
			}
		}
	}
	return bwp;
}