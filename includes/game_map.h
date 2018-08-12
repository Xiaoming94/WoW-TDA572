#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "map_tile.h"
#include "avancezlib.h"

#include <vector>
#include <string>

class GameMap
{
private:
	std::vector<MapTile*> tiles;
	int width; // Width in Tiles
	int height; // Height in Tiles
	bool * bpm; // binary Pixel Map
public:
	GameMap(
		std::string mapString,
		int width,
		int height
	);
	~GameMap();
};

GameMap CreateStandardMap();

#endif