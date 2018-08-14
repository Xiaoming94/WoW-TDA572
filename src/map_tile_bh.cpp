#include "map_tile_bh.h"
#include "SDL.h"

TileBH::TileBH(int row, int col) :
	MapTile(row, col)
{
	SDL_Log("MapTile :: TileBH");
}

std::string TileBH::getWallType()
{
	return TILE_BH;
}

bool ** TileBH::getBinaryWall()
{
	bool ** bwp = MapTile::getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
		for (int j = 0; j < SPRITE_SIDE; j++)
			if (j < 2 || j > SPRITE_SIDE - 3)
				bwp[i][j] = true;

	return bwp;
}