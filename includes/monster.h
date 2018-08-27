#ifndef MONSTER_H
#define MONSTER_H
#include "behaviour_component.h"
#include "game_object.h"
#include <iostream>

#define BURWOR "Burwor.bmp"
#define GARWOR "Garwor.bmp"
#define THORWOR "Thorwor.bmp"
#define WORLUK "Worluk.bmp"
#define WIZARD "Wizard.bmp"


class MonsterBehaviourComponent : public BehaviourComponent
{
public:
	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, GameMap * map, int x, int y)
	{
		BehaviourComponent::Create(system, go, game_objects, map);
		map->placeObject(go,x,y);
	}
	/**
	 * TODO: Implement Monster AI
	 */
	virtual void Update(float dt)
	{
		return;
	}
};

class Monster : public GameObject
{
public:
	virtual std::string GetMonsterType()
	{
		return "default monster";
	}
};

#include "burwor.h"
#include "wizard.h"
#include "garwor.h"
#include "thorwor.h"
#include "worluk.h"

#endif
