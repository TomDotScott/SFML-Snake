#pragma once
#include "Snake.h"

class AISnake : public Snake {
public:
	AISnake(int playerNumber);
	void ChooseDirection();

	//Cycle through the food on the screen to find the closest food to the snake
	void FindFood();
<<<<<<< Updated upstream
	
=======

	void Update(sf::RenderWindow& window) override;

>>>>>>> Stashed changes
	void CheckCollisionAgainstSelf();
	void CheckCollision() override;
	
	void SetOtherSnakes(AISnake* snakeToAdd) { m_otherSnakes.push_back(snakeToAdd); }
	
<<<<<<< Updated upstream
	void SetFood(Food* food) { m_food.push_back(food); }
	
	int GetPlayerNumber() const { return m_playerNumber; }

=======
>>>>>>> Stashed changes
private:
	//To deal with collisions between AI snakes
	std::vector<AISnake*> m_otherSnakes;

<<<<<<< Updated upstream
	//A store of all of the food on screen to help with decision making
	std::vector<Food*> m_food;

	int m_playerNumber;

=======
>>>>>>> Stashed changes
	//The front of the list is the closest food to the snake
	std::list<sf::Vector2f> m_foodList{};
};
