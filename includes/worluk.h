#ifndef WORLUK_H
#define WORLUK_H

class Worluk : public Monster
{
public:
	std::string GetMonsterType()
	{
		return WORLUK;
	}

	Message GetCollideMessage()
	{
		return Message::WORLUK_HIT;
	}
};

#endif