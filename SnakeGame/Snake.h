#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <list>
#include "Food.h"

using SnakeSegments = std::list<sf::Vector2f>;

//Holds the directions that the snake can travel in
enum class EDirection
{
	e_none, e_left, e_right, e_up, e_down
};

//To deal with collisions in the game
enum class ECollisionType {
	e_wall, e_snake, e_self, e_food
};

//Each part of the snake is a position vector called a Segment
struct Segment {
	int x;
	int y;
	Segment(const int x, const int y) : x(x), y(y) {
		sf::Vector2i(x, y);
	}
};

class Snake : public Entity
{
protected:
	EDirection m_direction{ EDirection::e_right };

	sf::RectangleShape m_rectangle;

	SnakeSegments m_segments;

	bool m_gobbleMode{ false };

	bool m_isDead{ false };

	void Move() override;

	void Render(sf::RenderWindow& window) override final;

	static int RandomRange(int min, int max);

public:
	Snake();

	void Grow(const int amount);

	void Shrink(const int amount);

	void Update(sf::RenderWindow& window);

	virtual void CheckCollision();

	//for colliding with other snakes, itself and walls
	void Collision(ECollisionType collisionType);

	//For colliding with pickups
	void Collision(Food* food);

	sf::Vector2f GetHeadPosition() const { return m_position; }

	int FindGobblePoint(sf::Vector2f gobbleSnakeHead);

	bool GetIsGobbleMode() const { return m_gobbleMode; }

	void SetIsGobbleMode(const bool& isGobbleMode) { m_gobbleMode = isGobbleMode; }

	bool GetIsDead() const { return m_isDead; }

	SnakeSegments GetSnakeSegments() const { return m_segments; }

};