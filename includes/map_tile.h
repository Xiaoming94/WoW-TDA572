#ifndef MAP_TILE_H
#define MAP_TILE_H

// Defining sprites
// Note that these are also the different Macros returned by getWallType() member function
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

#define MAP_OFFSET 64

#include <string>
#include "game_object.h"
#include "component.h"

/**
 * This Is the Base class for a MapTile
 * 
 * Every MapTile will be a subclass of this class
 * Mostly implemented in a stateless manor to avoid side effects.
 */

class MapTile :
	public GameObject
{
public:
	MapTile(int row, int col);
	~MapTile();
	/**
	 * Function getWallType();
	 * Returns a String defined by what type of wall the tiles represents
	 * All return strings are defined in the macros of this file
	 */
	virtual std::string getWallType();
	virtual bool ** getBinaryWall();
	//bool bwp[32][32] = { false }; // Binary Wall pixel	
};

void printBinaryMap(MapTile * tile);

RenderComponent * createTileRenderer(MapTile * tile, AvancezLib * system, std::set<GameObject*> * game_objects);
#endif
