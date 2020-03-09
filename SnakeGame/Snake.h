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

	void Move() override final;

	void Grow(int amount);

	void Render(sf::RenderWindow& window) override final;

public:
	Snake();
	void Update(sf::RenderWindow& window);
	void Input();
};