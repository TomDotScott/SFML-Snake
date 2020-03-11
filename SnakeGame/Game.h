#pragma once
#include "Snake.h"
#include "PlayerSnake.h"
#include "AISnake.h"
#include "Entity.h"
#include "Food.h"

class Game
{
private:
	PlayerSnake* m_playerSnake;
	std::vector<AISnake*> m_AISnakes;
	Food m_foodArray[5];
	sf::RenderWindow& m_window;

	int m_AISnakeAmount{ 5 };
public:
	void Update();
	void Input();
	Game(sf::RenderWindow& window);
	void CheckCollisions();
};