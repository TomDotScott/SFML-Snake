#include "Snake.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <assert.h>
#include "Constants.h"

int Snake::RandomRange(int min, int max) //range : [min, max)
{
	return min + rand() % ((max + 1) - min);
}

void Snake::Update(sf::RenderWindow& window) {
	Move();
	Render(window);
}


void Snake::Render(sf::RenderWindow& window) {
	if (!m_isDead) {
		for (auto itr = m_segments.begin(); itr != m_segments.end(); ++itr) {
			m_rectangle.setPosition(sf::Vector2f(itr->x, itr->y));
			window.draw(m_rectangle);
		}
	}
}

Snake::Snake()
{
	//Set random colours for the AI Snakes
	m_colour = sf::Color(RandomRange(0, 255), RandomRange(0, 255), RandomRange(0, 255));

	m_rectangle = sf::RectangleShape(sf::Vector2f((float)Constants::kSnakeBlockSize, (float)Constants::kSnakeBlockSize));
	m_rectangle.setFillColor(m_colour);
	m_rectangle.setPosition(m_position);
}

void Snake::Move() {
	//if the left arrow is pressed

	switch (m_direction)
	{
	case EDirection::eLeft:
		m_position.x -= (Constants::kSnakeBlockSize + 5);
		break;
	case EDirection::eRight:
		m_position.x += (Constants::kSnakeBlockSize + 5);
		break;
	case EDirection::eUp:
		m_position.y -= (Constants::kSnakeBlockSize + 5);
		break;
	case EDirection::eDown:
		m_position.y += (Constants::kSnakeBlockSize + 5);
		break;
	}

	CheckCollision();
	m_segments.pop_back();
	m_segments.push_front(sf::Vector2f(m_position.x, m_position.y));
}

void Snake::Grow(int amount)
{
	for (int i = 0; i < amount; ++i) {
		m_segments.push_back(sf::Vector2f(m_position.x, m_position.y));
	}
}

//check whether a snake has collided with itself
void Snake::CheckCollision() {
	if (m_direction != EDirection::eNone) {
		for (sf::Vector2f segment : m_segments) {
			if (segment == m_position && !m_isDead) {
				Collision(ECollisionType::eSelf);
			}
		}
	}
}

void Snake::Collision(ECollisionType collisionType) {
	switch (collisionType)
	{
	case ECollisionType::eWall:
		break;
	case ECollisionType::eSnake:
		break;
	case ECollisionType::eSelf:
		m_isDead = true;
		break;
	case ECollisionType::eFood:
		break;
	default:
		break;
	}
}

void Snake::Collision(Food& food)
{
	std::cout << "+" << food.GetGrowAmount() << std::endl;
	Grow(food.GetGrowAmount());
}
