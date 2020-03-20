#include "Snake.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <assert.h>
#include "Constants.h"

int Snake::RandomRange(int min, int max) {
	return min + rand() % ((max + 1) - min);
}

void Snake::Update(sf::RenderWindow& window) {
	Move();
	Render(window);
}


void Snake::Render(sf::RenderWindow& window) {
	if (!m_dead) {
		for (auto itr = m_segments.begin(); itr != m_segments.end(); ++itr) {
			m_rectangle.setPosition(sf::Vector2f(itr->x, itr->y));
			window.draw(m_rectangle);
		}
	}
}

Snake::Snake() {
	//Set random colours for the AI Snakes
	m_colour = sf::Color(RandomRange(0, 255), RandomRange(0, 255), RandomRange(0, 255));

	m_rectangle = sf::RectangleShape(sf::Vector2f(static_cast<float>(Constants::k_snakeBlockSize), static_cast<float>(Constants::k_snakeBlockSize)));
	m_rectangle.setFillColor(m_colour);
	m_rectangle.setPosition(m_position);
}

void Snake::Move() {
	switch (m_direction) {
	case EDirection::e_left:
		m_position.x -= (Constants::k_snakeBlockSize + 5);
		break;
	case EDirection::e_right:
		m_position.x += (Constants::k_snakeBlockSize + 5);
		break;
	case EDirection::e_up:
		m_position.y -= (Constants::k_snakeBlockSize + 5);
		break;
	case EDirection::e_down:
		m_position.y += (Constants::k_snakeBlockSize + 5);
		break;
	default:
		break;
	}

	CheckCollision();
	m_segments.pop_back();
	m_segments.push_front(sf::Vector2f(m_position.x, m_position.y));
}

void Snake::Grow(const int amount) {
	for (int i{ 0 }; i < amount; ++i) {
		m_segments.push_back(sf::Vector2f(m_position.x, m_position.y));
	}
}

//Find the point where a snake intersects and returns the position in the linked list.
//This point - the overall size will be the grow amount of the snake that collided with it
int Snake::FindGobblePoint(sf::Vector2f gobbleSnakeHead) const {
	if (!m_dead) {
		int counter{ 0 };
		for (auto itr = m_segments.begin(); itr != m_segments.end(); ++itr) {
			if (sf::Vector2f(itr->x, itr->y) == gobbleSnakeHead) {
				return counter;
			}
			counter++;
		}
	}
	return -1;
}

void Snake::Shrink(const int amount) {
	unsigned const int newSize = static_cast<signed int>(m_segments.size()) - amount;
	while (m_segments.size() != newSize) {
		m_segments.pop_back();
	}
}

//check whether a snake has collided with itself
void Snake::CheckCollision() {
	if (m_direction != EDirection::e_none) {
		for (sf::Vector2f segment : m_segments) {
			if (segment == m_position && !m_dead) {
				Collision(ECollisionType::e_self);
			}
		}
	}
}

void Snake::Collision(const ECollisionType collisionType) {
	if (!m_dead) {
		switch (collisionType) {
		case ECollisionType::e_wall:
			std::cout << "I HIT A WALL" << std::endl;
			m_dead = true;
			break;
		case ECollisionType::e_snake:
			std::cout << "I HIT ANOTHER SNAKE" << std::endl;
			m_dead = true;
			break;
		case ECollisionType::e_self:
			std::cout << "I HIT MYSELF" << std::endl;
			m_dead = true;
			break;
		case ECollisionType::e_food:
			break;
		default:
			break;
		}
	}
}

void Snake::Collision(Food* food)
{
	std::cout << "+" << food->GetGrowAmount() << std::endl;
	if (food->GetType() == eFoodType::e_gobble) {
		m_gobbleMode = true;
		std::cout << "GOBBLE MODE!" << std::endl;
	}
	Grow(food->GetGrowAmount());
}