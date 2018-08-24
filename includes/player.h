#include "game_map.h"

class PlayerBehaviourComponent : public BehaviourComponent
{
	float time_fire_pressed;	// time from the last time the fire button was pressed
	ObjectPool<Rocket> * rockets_pool;
	int playerNumber;

public:
	virtual ~PlayerBehaviourComponent() {}

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Rocket> * rockets_pool, int playerNum, GameMap * map)
	{
		BehaviourComponent::Create(system, go, game_objects, map);
		this->rockets_pool = rockets_pool;
		this->playerNumber = playerNum;
		if (playerNumber == 1) 
		{
			map -> placeObject(this->go, 0, map -> getHeight()-1);
		}
		else 
		{
			map -> placeObject(this->go, map -> getWidth()-1, map -> getHeight()-1);
		}
	}

	virtual void Init()
	{
		time_fire_pressed = -10000.f;
	}
	virtual void Update(float dt)
	{
		double change = dt * PLAYER_SPEED;
		AvancezLib::KeyStatus keys = 
			system->getKeyStatus(this -> playerNumber);
		if (keys.right && !map->isColliding(Direction::RIGHT, change ,this->go))
		{
			go->SetDirection(Direction::RIGHT);
			MoveHorizontal(change);
		}
			
		if (keys.left && !map->isColliding(Direction::LEFT, change, this ->go))
		{
			go->SetDirection(Direction::LEFT);
			MoveHorizontal(-1 * change);
		}
		if (keys.down && !map->isColliding(Direction::DOWN, change, this ->go))
		{
			go->SetDirection(Direction::DOWN);
			MoveVertical(change);
		}
			
		if (keys.up && !map->isColliding(Direction::UP, change, this ->go))
		{
			go->SetDirection(Direction::UP);
			MoveVertical(-1 * change);
		}
			
		if (keys.fire)
		{
			if (CanFire())
			{
				// fetches a rocket from the pool and use it in game_objects
				Rocket * rocket = rockets_pool->FirstAvailable();
				if (rocket != NULL)	// rocket is NULL is the object pool can not provide an object
				{
					rocket->Init(go->horizontalPosition, go->verticalPosition,go->GetDirection());
					game_objects->insert(rocket);
				}
			}
		}
	}


	// move the player left or right
	// param move depends on the time, so the player moves always at the same speed on any computer
	void MoveHorizontal(float move)
	{
		go->horizontalPosition = go -> horizontalPosition + move;
		if (go->horizontalPosition < 0)
			go->horizontalPosition = 0;
		if (go->horizontalPosition > 640 - 32)
			go->horizontalPosition = 640 - 32;
	}

	void MoveVertical(float move) {
		go->verticalPosition = go->verticalPosition + move;
		if (go->verticalPosition < 0)
			go->verticalPosition = 0;
		if (go->verticalPosition > 480 - 32)
			go->verticalPosition = 480 - 32;
	}

	// return true if enough time has passed from the previous rocket
	bool CanFire()
	{
		// shoot just if enough time passed by
		if ((system->getElapsedTime() - time_fire_pressed) < (FIRE_TIME_INTERVAL / game_speed))
			return false;

		time_fire_pressed = system->getElapsedTime();

		SDL_Log("fire!");
		return true;
	}
};


// the main player
class Player : public GameObject
{
public:

	int lives;	// it's game over when goes below zero 

	virtual ~Player()	{		SDL_Log("Player::~Player");	}

	virtual void Init()
	{
		SDL_Log("Player::Init");
		GameObject::Init();
		lives = NUM_LIVES;
	}

	virtual void Receive(Message m) 
	{
		if (m == HIT)
		{ 
			SDL_Log("Player::Hit!");
			RemoveLife();

			if (lives < 0)
				Send(GAME_OVER);
		}
	}

	void RemoveLife()
	{
		lives--;
		SDL_Log("remaining lives %d", lives);
	}
};
