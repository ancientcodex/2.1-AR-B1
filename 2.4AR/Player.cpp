#include "Player.h"

Player::Player(std::string name, int points) : name(name), points(points)
{
}

std::string Player::toString()
{
	std::string fullPlayer;
	fullPlayer = name + " with " + std::to_string(points) + " Points!";
	return fullPlayer;
}
