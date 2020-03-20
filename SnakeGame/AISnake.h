#pragma once
#include "Snake.h"
class AISnake : public Snake {
public:
	AISnake();
	void ChooseDirection();

	//Cycle through the food on the screen to find the closest food to the snake
	void FindFood();
	
	void Collision(Food* food) override;

	void Update(sf::RenderWindow& window) override;

	void CheckCollisionAgainstSelf();
	
	void SetFood(Food* food) { m_food.push_back(food); }
	
private:

	//A store of all of the food on screen to help with decision making
	std::vector<Food*> m_food;

	//The front of the list is the closest food to the snake
	std::list<sf::Vector2f> m_foodList{};
};
