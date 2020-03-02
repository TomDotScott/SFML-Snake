#pragma once
#include "Snake.h"
#include "Entity.h"
#include "Food.h"
class Game
{
private:
	Snake* m_playerSnake;
	std::vector<Food> m_food;
public:
	void Update(sf::RenderWindow& window);
	Game();
};

