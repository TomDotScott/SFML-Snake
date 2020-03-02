#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <list>

enum EDirection : int
{
	eLeft, eRight, eUp, eDown
};

class Snake : public Entity
{
private:
	float m_height{ 1 };
	EDirection m_direction{ EDirection::eRight };
	sf::RectangleShape m_rectangle;

	std::list<sf::RectangleShape> m_segments;
	void Move();
	void Input();
	void Render(sf::RenderWindow& window);
public:
	Snake(sf::Color colour, sf::Vector2f position, float height, sf::Vector2f speed);
	void Update(sf::RenderWindow& window);
};