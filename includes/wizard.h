#ifndef WIZARD_H
#define WIZARD_H

class Wizard : public Monster
{
public:
	std::string GetMonsterType()
	{
		return WIZARD;
	}

	Message GetCollideMessage()
	{
		return Message::WIZARD_HIT;
	}
};

#endif