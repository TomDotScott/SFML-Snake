#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <list>

using SnakeSegments = std::list<sf::Vector2i>;

const int k_Height = 16;

enum EDirection : int
{
	eLeft, eRight, eUp, eDown
};

struct Segment {
	int x;
	int y;
	Segment(int x, int y) : x(x), y(y) {
		sf::Vector2i(x, y);
	}
};

class Snake : public Entity
{
private:
	EDirection m_direction{ EDirection::eRight };
	sf::RectangleShape m_rectangle;

	SnakeSegments m_segments;

	void Move();
	void Input();
	void Render(sf::RenderWindow& window);
public:
	Snake(sf::Color colour, sf::Vector2f position, float height, sf::Vector2f speed);
	void Update(sf::RenderWindow& window);
};