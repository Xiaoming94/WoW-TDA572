#ifndef BEHAVIOUR_COMPONENT_H
#define BEHAVIOUR_COMPONENT_H

#include "component.h"
#include "game_map.h"
#include <queue>

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
	ObjectPool<GameObject> * targets;
	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, GameMap * map, ObjectPool<GameObject> * targets)
	{
		BehaviourComponent::Create(system, go, game_objects, map);

		this->targets = targets;
	}

	virtual void Update(float dt)
	{
		return;
	}

	virtual double Heuristics(double x, double y)
	{
		return 0.0;
	}


	// Path finding algorithm function
	virtual Direction FindDirection(
		double change,
		GameObject * target
	)
	{
		std::priority_queue<DirStruct> dirs;
		GameObject goCopy;
		if (!map->isColliding(Direction::LEFT, change, go))
		{
			goCopy.horizontalPosition = go->horizontalPosition - change;
			goCopy.verticalPosition = go->verticalPosition;
			dirs.push(DirStruct(Direction::LEFT, CalcDistance(goCopy, *target, Direction::LEFT, change)));
		}
			
	}

	int CalcDistance(GameObject go, GameObject target, Direction dir, double change)
	{
		return 0;
	}
};
#endif