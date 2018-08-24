#ifndef BEHAVIOUR_COMPONENT_H
#define BEHAVIOUR_COMPONENT_H

#include "component.h"
#include "game_map.h"

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


#endif