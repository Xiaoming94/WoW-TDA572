#ifndef BEHAVIOUR_COMPONENT_H
#define BEHAVIOUR_COMPONENT_H

#include "component.h"
#include "game_map.h"
#include <queue>
#include <cmath>
#include <vector>

class BehaviourComponent : public Component
{
protected:
	GameMap * map;
public:
	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, GameMap * map)
	{
		Component::Create(system, go, game_objects);

		this->map = map;
	}
};

class AIBehaviourComponent : public BehaviourComponent
{
public:
	struct DirStruct
	{
		Direction dir;
		int ticks;
		
		DirStruct(
			Direction dir,
			int ticks
		)
		{
			this->dir = dir;
			this->ticks = ticks;
		}

		bool operator<(const struct DirStruct& rhs) const
		{
			return ticks < rhs.ticks;
		}
	};

	struct PathNode {
		GameObject go;
		Direction lastDir;
		int ticks;
		double value; //Ticks + Heuristics
		PathNode(GameObject go, Direction lastDir,int ticks, double value)
		{
			this->go = go;
			this->value = value;
			this->ticks = ticks;
			this->lastDir = lastDir;
		}

		bool operator<(const struct PathNode& rhs) const
		{
			return value < rhs.value;
		}
	};
	ObjectPool<GameObject> * targets;
	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, GameMap * map, ObjectPool<GameObject> * targets)
	{
		BehaviourComponent::Create(system, go, game_objects, map);

		this->targets = targets;
	}

	virtual void Update(float dt)
	{
		
	}

	virtual double Heuristics(GameObject go, double x, double y)
	{
		return 0.0;
	}

	void Move(Direction dir,double change)
	{
		switch (dir)
		{
		case Direction::LEFT :
			this->go->horizontalPosition -= change;
			break;
		case Direction::RIGHT :
			this->go->horizontalPosition += change;
			break;
		case Direction::UP :
			this->go->verticalPosition -= change;
			break;
		case Direction::DOWN :
			this->go->verticalPosition += change;
			break;
		}
	}
	// Below this comments are utility functions useful for the AIs

	// Path finding algorithm function
	virtual Direction FindDirection(
		double change,
		GameObject * target
	)
	{
		std::priority_queue<DirStruct> dirs;
		GameObject goCopy;
		if (!(map->isColliding(Direction::LEFT, change, go)))
		{
			goCopy.horizontalPosition = go->horizontalPosition - change;
			goCopy.verticalPosition = go->verticalPosition;
			dirs.push(DirStruct(Direction::LEFT, CalcDistance(goCopy, *target, Direction::LEFT, change)));
		}
		if (!(map->isColliding(Direction::RIGHT, change, go)))
		{
			goCopy.horizontalPosition = go->horizontalPosition - change;
			goCopy.verticalPosition = go->verticalPosition;
			dirs.push(DirStruct(Direction::RIGHT, CalcDistance(goCopy, *target, Direction::RIGHT, change)));
		}
		if (!(map->isColliding(Direction::UP, change, go)))
		{
			goCopy.horizontalPosition = go->horizontalPosition - change;
			goCopy.verticalPosition = go->verticalPosition;
			dirs.push(DirStruct(Direction::UP, CalcDistance(goCopy, *target, Direction::UP, change)));
		}
		if (!(map->isColliding(Direction::DOWN, change, go)))
		{
			goCopy.horizontalPosition = go->horizontalPosition - change;
			goCopy.verticalPosition = go->verticalPosition;
			dirs.push(DirStruct(Direction::DOWN, CalcDistance(goCopy, *target, Direction::DOWN, change)));
		}

		return dirs.top().dir;
			
	}

	int CalcDistance(GameObject go, GameObject target, Direction dir, double change)
	{
		std::priority_queue<PathNode> queue;
		return CalcDistanceAstar(go, target, dir, change, queue, 1);
	}
	
	int CalcDistanceAstar(GameObject go, GameObject target, Direction dir, double change, std::priority_queue<PathNode> &queue, int ticks)
	{
		if (AtDestination(go, target))
			return ticks;

		queue.pop();
		std::vector<Direction> availableDirs = getAvailableDirections(dir, go, change);

		for (Direction d : availableDirs)
		{
			GameObject newGo;
			newGo.horizontalPosition = go.horizontalPosition;
			newGo.verticalPosition = go.verticalPosition;
			switch (d)
			{
			case Direction::LEFT :
				newGo.horizontalPosition -= change;
				break;
			case Direction::RIGHT :
				newGo.horizontalPosition += change;
				break;
			case Direction::UP :
				newGo.verticalPosition -= change;
				break;
			case Direction::DOWN :
				newGo.verticalPosition += change;
				break;
			default :
				break;
			}
			PathNode newNode(newGo, d, ticks + 1, ticks + 1 + Heuristics(newGo, target.horizontalPosition, target.verticalPosition));
			queue.push(newNode);
		}
		PathNode nextNode = queue.top();
		return CalcDistanceAstar(nextNode.go, target, nextNode.lastDir, change, queue, nextNode.ticks);
	}

	bool AtDestination(GameObject go, GameObject target)
	{
		return std::abs(target.horizontalPosition - go.horizontalPosition) < SPRITE_SIDE
			|| std::abs(target.verticalPosition - go.horizontalPosition) < SPRITE_SIDE;
	}

	std::vector<Direction> getAvailableDirections(Direction lastDir, GameObject go, double change)
	{
		std::vector<Direction> dirs;
		switch(lastDir)
		{
		case Direction::LEFT :
			if(isAvailableDirection(go, Direction::LEFT, change))
				dirs.push_back(Direction::LEFT);
			if(isAvailableDirection(go, Direction::UP, change))
				dirs.push_back(Direction::UP);
			if(isAvailableDirection(go, Direction::DOWN, change))
				dirs.push_back(Direction::DOWN);
			return dirs;
		case Direction::RIGHT :
			if (isAvailableDirection(go, Direction::RIGHT, change))
				dirs.push_back(Direction::RIGHT);
			if (isAvailableDirection(go, Direction::UP, change))
				dirs.push_back(Direction::UP);
			if (isAvailableDirection(go, Direction::DOWN, change))
				dirs.push_back(Direction::DOWN);
			return dirs;
		case Direction::UP :
			if (isAvailableDirection(go, Direction::UP, change))
				dirs.push_back(Direction::UP);
			if (isAvailableDirection(go, Direction::LEFT, change))
				dirs.push_back(Direction::LEFT);
			if (isAvailableDirection(go, Direction::RIGHT, change))
				dirs.push_back(Direction::RIGHT);
			return dirs;
		case Direction::DOWN :
			if (isAvailableDirection(go, Direction::DOWN, change))
				dirs.push_back(Direction::UP);
			if (isAvailableDirection(go, Direction::LEFT, change))
				dirs.push_back(Direction::LEFT);
			if (isAvailableDirection(go, Direction::RIGHT, change))
				dirs.push_back(Direction::RIGHT);
			return dirs;

		default :
			return dirs;
		}
	}

	bool isAvailableDirection(GameObject go, Direction dir, double change)
	{
		return !(map->isColliding(dir, change, &go));
	}
};
#endif