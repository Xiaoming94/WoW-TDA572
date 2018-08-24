#include "game_map.h"
#include <sstream>
#include <iostream>

bool ** initBinaryMap(int width, int height)
{
	bool ** bpm = new bool*[height * SPRITE_SIDE];
	for (int i = 0; i < height * SPRITE_SIDE; i++)
		bpm[i] = new bool[width * SPRITE_SIDE];
	return bpm;
}

void fillBinaryMap(bool ** bpm, int row, int col, MapTile * tile)
{
	bool ** bwp = tile->getBinaryWall();
	for (int i = 0; i < SPRITE_SIDE; i++)
	{
		for (int j = 0; j < SPRITE_SIDE; j++)
		{
			bpm[row * SPRITE_SIDE + i][col * SPRITE_SIDE + j] =
				bwp[i][j];
		}
	}
}

MapTile * buildMapTile(std::string tileToken, int row, int col) {
	if (!tileToken.compare("bh"))
	{
		return new TileBH(row,col);
	}
	if (!tileToken.compare("bv"))
	{
		return new TileBV(row,col);
	}
	if (!tileToken.compare("ctl"))
	{
		return new TileCTL(row,col);
	}
	if (!tileToken.compare("ctr"))
	{
		return new TileCTR(row,col);
	}
	if (!tileToken.compare("cbl"))
	{
		return new TileCBL(row,col);
	}
	if (!tileToken.compare("cbr"))
	{
		return new TileCBR(row,col);
	}
	if (!tileToken.compare("u"))
	{
		return new TileUp(row,col);
	}
	if (!tileToken.compare("l"))
	{
		return new TileLeft(row,col);
	}
	if (!tileToken.compare("r"))
	{
		return new TileRight(row,col);
	}
	if (!tileToken.compare("d"))
	{
		return new TileDown(row,col);
	}
	else
	{
		return new MapTile(row,col);
	}
}

GameMap::GameMap(
	std::string mapString,
	int width,
	int height,
	AvancezLib * system,
	std::set<GameObject*> * game_objects
)
{
	this->bpm = initBinaryMap(width, height);
	this->width = width;
	this->height = height;
	std::istringstream mss = std::istringstream(mapString);
	std::string line;
	int row = 0;
	while (std::getline(mss, line, '\n'))
	{
		std::istringstream tilestring = std::istringstream(line);
		std::string tileToken;
		int col = 0;
		while (std::getline(tilestring, tileToken, ','))
		{
			MapTile * tile = buildMapTile(tileToken,row,col);
			tiles.push_back(tile);
			fillBinaryMap(bpm, row, col, tile);
			col++;
		}
		row++;
	}
	std::cout << "Num Of Tiles: " << tiles.size() << std::endl;
	std::cout << "Width: " << this->width;
	std::cout << " height: " << this->height;
	std::cout << std::endl;
	for (MapTile * tile : tiles)
	{
		RenderComponent * tileRenderer = createTileRenderer(tile, system, game_objects);
		tile -> AddComponent(tileRenderer);
	}

	SDL_Log("GameMap Created");
}


GameMap::~GameMap()
{
	SDL_Log("GameMap Destroyed");
}

bool GameMap::collidingLeft(int x, int  y)
{
	for (int i = x + 3; i < x + SPRITE_SIDE - 3; i++)
		for (int j = y + 3; j < y + SPRITE_SIDE - 3; j++)
			if (this->bpm[j][i])
				return true;
	return false;
}

bool GameMap::collidingRight(int x, int y)
{
	for (int i = x + SPRITE_SIDE - 3; i > x + 3; i--)
		for (int j = y + 3; j < y + SPRITE_SIDE - 3; j++)
			if (this->bpm[j][i])
				return true;
	return false;
}

bool GameMap::collidingUp(int x, int y)
{
	for (int i = y + 3; i < y + SPRITE_SIDE - 3; i++)
		for (int j = x + 3; j < x + SPRITE_SIDE - 3; j++)
			if (this->bpm[i][j])
				return true;
	return false;
}

bool GameMap::collidingDown(int x, int y)
{
	for (int i = y + SPRITE_SIDE - 3; i > y + 3; i--)
		for (int j = x + 3; j < x + SPRITE_SIDE - 3; j++)
			if (this->bpm[i][j])
				return true;
	return false;
}

void GameMap::renderMap(float dt)
{
	for (MapTile * tile : tiles)
	{
		tile -> Update(dt);
	}
}

void GameMap::printBinaryMap()
{
	std::cout << "[\n";
	for (int i = 0; i < SPRITE_SIDE * height; i++)
	{
		std::cout << "\t";
		for (int j = 0; j < SPRITE_SIDE * width; j++)
		{
			std::cout << this->bpm[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "]";
}

void GameMap::placeObject(GameObject * go, int x, int y)
{
	MapTile * tile = tiles.at(this -> width * y + x);
	go->horizontalPosition = tile->horizontalPosition;
	go->verticalPosition = tile->verticalPosition;
}

int GameMap::getWidth() { return this->width; }
int GameMap::getHeight() { return this->height; }

bool GameMap::isColliding(Direction dir, double change, GameObject * go)
{
	switch (dir)
	{
	case Direction::UP :
		return collidingUp(
			(int)(go->horizontalPosition - MAP_OFFSET), 
			(int)(go->verticalPosition - change - MAP_OFFSET)
		);
	case Direction::DOWN :
		return collidingDown(
			(int)(go->horizontalPosition - MAP_OFFSET), 
			(int)(go->verticalPosition + change - MAP_OFFSET)
		);
	case Direction::LEFT :
		return collidingLeft(
			(int)(go->horizontalPosition - change - MAP_OFFSET),
			(int)(go->verticalPosition - MAP_OFFSET) 
		);
	case Direction::RIGHT :
		return collidingRight(
			(int)(go->horizontalPosition + change - MAP_OFFSET), 
			(int)(go->verticalPosition - MAP_OFFSET)
		);
	}
}

GameMap * CreateStandardMap(
	AvancezLib * system,
	std::set <GameObject*> * game_objects	
)
{
	std::string standardMap = "ctl,bv,bv,u,u,u,bv,bv,ctr\n";
	standardMap = standardMap + "bh,ctl,bv,bh,bh,bh,bv,ctr,bh\n";
	standardMap = standardMap + "bh,cbl,bv,r,bh,l,bv,cbr,bh\n";
	standardMap = standardMap + "l,bv,bv,e,e,e,bv,bv,r\n";
	standardMap = standardMap + "bh,ctl,bv,r,bh,l,bv,ctr,bh\n";
	standardMap = standardMap + "bh,cbl,bv,bh,bh,bh,bv,cbr,bh\n";
	standardMap = standardMap + "cbl,bv,bv,d,d,d,bv,bv,cbr";

	return CreateMap(standardMap, system, game_objects);
}

GameMap * CreateMap(std::string mapString, AvancezLib * system, std::set<GameObject*> * game_objects)
{
	int width = 0;
	int height = 0;
	std::istringstream mss = std::istringstream(mapString);
	std::string line;
	int row = 0;
	while (std::getline(mss, line, '\n'))
	{
		std::istringstream lineSS = std::istringstream(line);
		std::string tileToken;
		int col = 0;
		while (std::getline(lineSS, tileToken, ','))
		{
			col++;
		}
		if (col > width)
			width = col;
		row++;
	}
	height = row;
	return new GameMap(mapString, width, height, system, game_objects);
}

