#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <list>
#include "Food.h"

using SnakeSegments = std::list<sf::Vector2f>;

//Holds the directions that the snake can travel in
enum class EDirection
{
	eNone, eLeft, eRight, eUp, eDown
};

//To deal with collisions in the game
enum class ECollisionType {
	eWall, eSnake, eSelf, eFood
};

//Each part of the snake is a position vector called a Segment
struct Segment {
	int x;
	int y;
	Segment(int x, int y) : x(x), y(y) {
		sf::Vector2i(x, y);
	}
};

class Snake : public Entity
{
protected:
	EDirection m_direction{ EDirection::eNone };

	sf::RectangleShape m_rectangle;

	SnakeSegments m_segments;

	bool m_isDead{ false };

	void Move();

	void Grow(int amount);

	void Render(sf::RenderWindow& window) override final;
	
	int RandomRange(int min, int max);

public:
	Snake();

	void Update(sf::RenderWindow& window);

	void CheckCollision();

	//for colliding with other snakes, itself and walls
	void Collision(ECollisionType collisionType);

	//For colliding with pickups
	void Collision(Food& food);

	sf::Vector2f GetHeadPosition() { return m_position; }

	bool GetIsDead() { return m_isDead; }

	SnakeSegments GetSnakeSegments() { return m_segments; }

};