#pragma once
#include "Snake.h"
#include "Entity.h"
#include "Food.h"
class Game
{
private:
	Snake* m_playerSnake;
	std::vector<Food> m_food;
	sf::RenderWindow& m_window;

public:
	void Update();
	void Input();
	Game(sf::RenderWindow& window);
};