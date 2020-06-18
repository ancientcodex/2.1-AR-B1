#pragma once
#include <string>

class Player
{
public:
	std::string name;
	int points;

	Player(std::string name, int points);
	std::string toString();
};

