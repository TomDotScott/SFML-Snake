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
<<<<<<< HEAD
	void SetFood(Food const food) { m_food.push_back(food); }
	void SetFood(Food const food, int pos) { m_food[pos] = food; }
=======
>>>>>>> parent of cf9d80a... Ai Pathfinding
	int GetPlayerNumber() const { return m_playerNumber; }

private:
	//To deal with collisions between AI snakes
	std::vector<AISnake*> m_otherSnakes;
	//A store of all of the food on screen to help with decision making
<<<<<<< HEAD
	std::vector<Food> m_food;
	
=======
	std::vector<Food*> m_food;
>>>>>>> parent of cf9d80a... Ai Pathfinding
	int m_playerNumber;
};

