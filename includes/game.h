
bool change_direction = false;

#include "game_map.h"

class Game : public GameObject
{
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/

	AvancezLib* system;

	ObjectPool<Rocket> rockets_pool;	// used to instantiate rockets

	Player * player1;
	Player * player2;

	Sprite * life_sprite;

	GameMap * gameMap;
	bool game_over;

	ObjectPool<GameObject> * monsterPool = new ObjectPool<GameObject>();

public:

	virtual void Create(AvancezLib* system)
	{
		SDL_Log("Game::Create");

		this->system = system;
		gameMap = CreateStandardMap(system, &game_objects);

		// Set Prop Player1
		player1 = new Player();
		PlayerBehaviourComponent * player1_behaviour = new PlayerBehaviourComponent();
		player1_behaviour->Create(system, player1, &game_objects, &rockets_pool,1,gameMap);
		RenderComponent * player1_render = new RenderComponent();
		player1_render->Create(system, player1, &game_objects, "WorriorBlue.bmp");

		player1->Create();
		player1->AddComponent(player1_behaviour);
		player1->AddComponent(player1_render);
		player1->AddReceiver(this);
		
		// Set Prop Player2
		player2 = new Player();
		PlayerBehaviourComponent * player2_behaviour = new PlayerBehaviourComponent();
		player2_behaviour->Create(system, player2, &game_objects, &rockets_pool,2,gameMap);
		RenderComponent * player2_render = new RenderComponent();
		player2_render->Create(system, player2, &game_objects, "WorriorGold.bmp");

		player2->Create();
		player2->AddComponent(player2_behaviour);
		player2->AddComponent(player2_render);
		player2->AddReceiver(this);

		game_objects.insert(player1);
		game_objects.insert(player2);

		Monster * monster1 = new Burwor();
		MonsterBehaviourComponent * monster1_behaviour = new MonsterBehaviourComponent();
		monster1_behaviour->Create(system, monster1, &game_objects, gameMap, 0, 0);
		RenderComponent * monster1_render = createMonsterRender(system, &game_objects, monster1);
		monster1->Create();
		monster1->AddComponent(monster1_behaviour);
		monster1->AddComponent(monster1_render);
		game_objects.insert(monster1);
		monsterPool->pool.push_back(monster1);

		Monster * monster2 = new Thorwor();
		MonsterBehaviourComponent * monster2_behaviour = new MonsterBehaviourComponent();
		monster2_behaviour->Create(system, monster2, &game_objects, gameMap, 0, 1);
		RenderComponent * monster2_render = createMonsterRender(system, &game_objects, monster2);
		monster2->Create();
		monster2->AddComponent(monster2_behaviour);
		monster2->AddComponent(monster2_render);
		game_objects.insert(monster2);
		monsterPool->pool.push_back(monster2);

		rockets_pool.Create(30);
		for (auto rocket = rockets_pool.pool.begin(); rocket != rockets_pool.pool.end(); rocket++)
		{
			RocketBehaviourComponent * behaviour = new RocketBehaviourComponent();
			behaviour->Create(system, *rocket, &game_objects);
			RenderComponent * render = new RenderComponent();
			CollideComponent * collider = new CollideComponent();
			collider->Create(system, *rocket, &game_objects, monsterPool);
			render->Create(system, *rocket, &game_objects, "rocket.bmp");
			(*rocket)->Create();
			(*rocket)->AddComponent(behaviour);
			(*rocket)->AddComponent(render);
			(*rocket)->AddComponent(collider);
		}

		// CREATE MONSTERS


		life_sprite = system->createSprite("player.bmp");
	}

	virtual void Init()
	{
		player1->Init();
		player2->Init();
		for (GameObject * go : monsterPool->pool)
		{
			go->Init();
		}
		enabled = true;
		game_over = false;
	}

	virtual void Update(float dt)
	{
		if (IsGameOver())
			dt = 0.f;

		gameMap->renderMap(dt);
		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Update(dt);
	}

	virtual void Draw()
	{
		char msg[1024];
		sprintf(msg, "%07d", 100);
		system->drawText(300, 32, msg);
		sprintf(msg, "bonus: %.1fX", game_speed);
		system->drawText(510, 32, msg);

		for (int i = 0; i < player1->lives; i++)
			life_sprite->draw(i*36+20, 16);

		if (IsGameOver())
		{
			sprintf(msg, "*** G A M E  O V E R ***");
			system->drawText(250, 8, msg);
		}
	}

	virtual void Receive(Message m)
	{
		if (m == GAME_OVER)
			game_over = true;
	}


	bool IsGameOver()
	{
		return game_over;
	}

	virtual void Destroy()
	{
		SDL_Log("Game::Destroy");

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Destroy();

		life_sprite->destroy();
	
		rockets_pool.Destroy();
		delete player1;
	}
};