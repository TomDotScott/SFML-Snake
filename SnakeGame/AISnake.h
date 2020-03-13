#pragma once
#include "Snake.h"
class AISnake : public Snake
{
public:
	AISnake(int playerNumber);
	void ChooseDirection();
	
	void CheckCollisionAgainstSelf();
	void CheckCollision() override;
	void SetOtherSnakes(AISnake* snakeToAdd) { m_otherSnakes.push_back(snakeToAdd); }
	int GetPlayerNumber() const { return m_playerNumber; }

private:
	//To deal with collisions between AI snakes
	std::vector<AISnake*> m_otherSnakes;
	//A store of all of the food on screen to help with decision making
	std::vector<Food*> m_food;
	int m_playerNumber;
};

