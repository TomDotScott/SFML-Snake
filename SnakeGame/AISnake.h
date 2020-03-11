#pragma once
#include "Snake.h"
class AISnake : public Snake
{
public:
	AISnake();
private:
	void ChooseDirection();
};

