#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// GameObject represents objects which moves are drawn
#include <vector>

#define SPRITE_SIDE 32

enum Message { 
	HIT, 
	GAME_OVER, 
	LEVEL_WIN, 
	NO_MSG, 
	GARWOR_HIT,
	BURWOR_HIT,
	THORWOR_HIT,
	WORLUK_HIT,
	WIZARD_HIT,
	PLAYER_HIT
};

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class Component;

class GameObject
{
protected:
	std::vector<GameObject*> receivers;
	std::vector<Component*> components;
	Direction dir;

public:
	double horizontalPosition;
	double verticalPosition;
	bool enabled;

	virtual ~GameObject();

	virtual void Create();
	virtual void AddComponent(Component * component);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	virtual void AddReceiver(GameObject *go);
	virtual void Receive(Message m) {}
	virtual Message GetCollideMessage();
	virtual void SetDirection(Direction dir);
	virtual Direction GetDirection();
	void Send(Message m);
};

#endif