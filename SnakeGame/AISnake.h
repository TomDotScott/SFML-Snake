#pragma once
#include "Snake.h"
class AISnake : public Snake {
public:
	AISnake();
	void ChooseDirection();
	
	void Update(sf::RenderWindow& window) override;

	//Cycle through the food on the screen to find the closest food to the snake
	void FindFood();
	
	void CheckCollisionAgainstSelf();
	
	void CheckCollision() override;

private:

	//The front of the list is the closest food to the snake
	std::list<sf::Vector2f> m_foodList{};
};
