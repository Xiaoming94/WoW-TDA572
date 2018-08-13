#ifndef MAP_TILE_H
#define MAP_TILE_H

// Defining sprites
// Starting with tiles that got walls on both sides
#define TILE_BH "WallBoth-Hori.bmp"
#define TILE_BV "WallBoth-Vert.bmp"

// Corners
#define TILE_CBL "WallcornerBL.bmp"
#define TILE_CBR "WallcornerBR.bmp"
#define TILE_CTL "WallcornerTL.bmp"
#define TILE_CTR "WallcornerTR.bmp"

// Singels
#define TILE_UP "WallUp.bmp"
#define TILE_DOWN "WallDown.bmp"
#define TILE_LEFT "WallLeft.bmp"
#define TILE_RIGHT "WallRight.bmp"

#include <string>
#include "game_object.h"

class MapTile :
	public GameObject
{
public:
	MapTile();
	~MapTile();
	virtual std::string getWallType();
	virtual bool ** getBinaryWall();
	//bool bwp[32][32] = { false }; // Binary Wall pixel	
};

/*class MapTileRenderComponent :
	public RenderComponent
{

};*/

void printBinaryMap(MapTile * tile);
#endif
