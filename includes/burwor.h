#ifndef BURWOR_H
#define BURWOR_H

class Burwor : public Monster
{
public:
	std::string GetMonsterType()
	{
		return BURWOR;
	}
	Message GetCollideMessage()
	{
		return Message::BURWOR_HIT;
	}
};

#endif