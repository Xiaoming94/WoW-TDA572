
class RocketBehaviourComponent : public Component
{
public:

	void Update(float dt)
	{
		if (go -> GetDirection() == Direction::UP)
			go->verticalPosition -= ROCKET_SPEED * dt; // rocket_speed * time
		if (go->GetDirection() == Direction::DOWN)
			go->verticalPosition += ROCKET_SPEED * dt;
		if (go->GetDirection() == Direction::LEFT)
			go->horizontalPosition -= ROCKET_SPEED * dt;
		if (go->GetDirection() == Direction::RIGHT)
			go->horizontalPosition += ROCKET_SPEED * dt;
		if (go->verticalPosition < 0) // When the rocket reaches the top of the screen, it disappears.
			go->enabled = false;
	}
};


// rockets are shot by the player towards the aliens
class Rocket : public GameObject
{
public:
	GameObject * source;
	virtual void Init(double xPos, double yPos, Direction dir, GameObject * source)
	{
		SDL_Log("Rocket::Init");
		GameObject::Init();

		horizontalPosition = xPos;
		verticalPosition = yPos;
		this->dir = dir;
		this->source = source;
	}

	virtual void Receive(Message m)
	{
		if (!enabled)
			return;

		if (m != HIT)
		{
			source->Receive(m);
		}
		enabled = false;
		SDL_Log("Rocket::Hit");
	}
};