#pragma once
#include "Snake.h"
#include "PlayerSnake.h"
#include "AISnake.h"
#include "Entity.h"
#include "Food.h"

struct Wall {
	float m_height, m_width;
	sf::Vector2f m_position;
	sf::RectangleShape m_wall;
	sf::Color m_colour = sf::Color::White;
	Wall(const float height, const float width, const sf::Vector2f position) : m_height(height), m_width(width), m_position(position) {
		m_wall = sf::RectangleShape(sf::Vector2f(width, height));
		m_wall.setFillColor(m_colour);
		m_wall.setPosition(m_position);
	}
};

class Game
{
private:
	PlayerSnake* m_playerSnake;
	std::vector<AISnake*> m_AISnakes;
	Food* m_foodArray[5];
	sf::RenderWindow& m_window;

	//TOP
	Wall m_topWall = Wall(25, Constants::k_screenWidth, sf::Vector2f(0, 0));
	//LEFT
	Wall m_leftWall = Wall(Constants::k_screenHeight, 25, sf::Vector2f(0, 0));
	//BOTTOM
	Wall m_bottomWall = Wall(25, Constants::k_screenWidth, sf::Vector2f(0, Constants::k_screenHeight - 25));
	//RIGHT
	Wall m_rightWall = Wall(Constants::k_screenHeight, 100, sf::Vector2f(Constants::k_screenWidth - 25, 0));

	int m_AISnakeAmount{ 5 };
public:
	void Update();
	void Input() const;
	Game(sf::RenderWindow& window);
	void CheckCollisions();
};