#pragma once
#include "Snake.h"
class AISnake : public Snake {
public:
	AISnake();
	void ChooseDirection();
	
	void Update() override;

	//Cycle through the food on the screen to find the closest food to the snake
	void FindFood();

private:

	//The front of the list is the closest food to the snake
	List m_foodList{};
};
