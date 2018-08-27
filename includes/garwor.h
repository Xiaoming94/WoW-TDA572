#ifndef GARWOR_H
#define GARWOR_H

class Garwor : public Monster
{
public:
	std::string GetMonsterType()
	{
		return GARWOR;
	}
	Message GetCollideMessage()
	{
		return Message::GARWOR_HIT;
	}
};

#endif