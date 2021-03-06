#ifndef GAME_MAP_H
#define GAME_MAP_H

// INCLUDING THE TILES

#include "map_tile.h"
#include "map_tile_bh.h"
#include "map_tile_bv.h"
#include "map_tile_cbl.h"
#include "map_tile_cbr.h"
#include "map_tile_ctl.h"
#include "map_tile_ctr.h"
#include "map_tile_left.h"
#include "map_tile_right.h"
#include "map_tile_up.h"
#include "map_tile_down.h"


#include "avancezlib.h"

#include <vector>
#include <string>

class GameMap
{
private:
	std::vector<MapTile*> tiles;
	bool ** bpm; // binary Pixel Map
	int width;
	int height;
	bool collidingLeft(int x, int y);
	bool collidingRight(int x, int y);
	bool collidingUp(int x, int y);
	bool collidingDown(int x, int y);
public:
	GameMap(
		std::string mapString,
		int width,
		int height,
		AvancezLib * system,
		std::set<GameObject*> * game_objects
	);
	~GameMap();
	void renderMap(float dt);
	void printBinaryMap();
	void placeObject(GameObject * go, int x, int y);
	int getWidth();
	int getHeight();
	bool isColliding(Direction dir, double change, GameObject * go);
};

GameMap * CreateStandardMap(AvancezLib * system, std::set<GameObject*> * game_objects);
GameMap * CreateMap(std::string mapString, AvancezLib * system, std::set<GameObject*> * game_objects);


#endif