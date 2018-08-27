#ifndef THORWOR_H
#define THORWOR_H

class Thorwor : public Monster
{
public:
	std::string GetMonsterType()
	{
		return THORWOR;
	}

	Message GetCollideMessage()
	{
		return Message::THORWOR_HIT;
	}
};

#endif