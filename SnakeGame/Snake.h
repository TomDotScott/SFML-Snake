#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <list>

using SnakeSegments = std::list<sf::Vector2i>;

const int k_Height = 20;

enum class EDirection
{
	eNone, eLeft, eRight, eUp, eDown
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
	EDirection m_direction{ EDirection::eNone };

	sf::RectangleShape m_rectangle;

	SnakeSegments m_segments;

	bool m_isDead{ false };

	void Move() override final;

	void Grow(int amount);

	void Render(sf::RenderWindow& window) override final;
	
	int RandomRange(int min, int max);

public:
	Snake();
	void Update(sf::RenderWindow& window);
	void Input();
	void CheckCollision();
	void Collision(std::string collisionType);
	sf::Vector2f GetPosition() { return m_position; }
};