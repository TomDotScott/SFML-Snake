#pragma once
#include "Snake.h"
class AISnake : public Snake
{
public:
	AISnake(int playerNumber);
	void ChooseDirection();
	void CheckCollision();
	void SetOtherSnakes(AISnake* snakeToAdd) { m_otherSnakes.push_back(snakeToAdd); }
	int GetPlayerNumber() { return m_playerNumber; }

private:
	//To deal with collisions between AI snakes
	std::vector<AISnake*> m_otherSnakes;
	int m_playerNumber;
};

