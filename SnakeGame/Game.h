#pragma once
#include "Snake.h"
#include "PlayerSnake.h"
#include "Entity.h"
#include "Food.h"

class Game
{
private:
	PlayerSnake* m_playerSnake;
	Food m_foodArray[5];
	sf::RenderWindow& m_window;
public:
	void Update();
	void Input();
	Game(sf::RenderWindow& window);
	void CheckCollisions();
};