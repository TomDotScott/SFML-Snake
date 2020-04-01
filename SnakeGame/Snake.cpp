#include "Snake.h"
#include "SFML/Graphics.hpp"
#include "Constants.h"

void Snake::Update() {
	if (!IsDead()) {
		m_score += 1;
		Move();
	}
}


void Snake::Render(sf::RenderWindow& _window) {
	if (!m_dead) {
		if (!m_segments.IsEmpty()) {
			auto* currentNode = m_segments.GetHead();
			for(int i = 0; i < m_segments.Size(); ++i)
			{
				if(i == 0)
				{
					m_rectangle.setFillColor(sf::Color::White);
				}
				else {
					m_rectangle.setFillColor(m_gobbleMode ? m_gobbleColour : m_defaultColour);
				}
				m_rectangle.setPosition(currentNode->m_position);
				_window.draw(m_rectangle);
				currentNode = currentNode->m_nextNode;
			}
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
		m_position.x -= (Constants::k_gridSize);
		break;
	case EDirection::e_right:
		m_position.x += (Constants::k_gridSize);
		break;
	case EDirection::e_up:
		m_position.y -= (Constants::k_gridSize);
		break;
	case EDirection::e_down:
		m_position.y += (Constants::k_gridSize);
		break;
	default:
		break;
	}

	CheckCollision();
	m_segments.PopBack();
	m_segments.PushFront(sf::Vector2f(m_position.x, m_position.y));
}

void Snake::Grow(const int _amount) {
	for (int i{ 0 }; i < _amount; ++i) {
		m_segments.PushBack(sf::Vector2f(m_position.x, m_position.y));
	}
	m_score += 10 * _amount;
}

//Find the point where a snake intersects and returns the position in the linked list.
//This point - the overall size will be the grow amount of the snake that collided with it
int Snake::FindGobblePoint(sf::Vector2f _gobbleSnakeHead) const {
	if (!m_dead) {
		int counter{ 0 };
		if (!m_segments.IsEmpty()) {
			auto* currentNode = m_segments.GetHead();
			while (currentNode->m_nextNode)
			{
				if (currentNode->m_position == _gobbleSnakeHead)
				{
					return counter;
				}
				currentNode = currentNode->m_nextNode;
				++counter;
			}
		}
	}
	return -1;
}

void Snake::Shrink(const int _amount) {
	if (!m_segments.IsEmpty()) {
		const int newSize = m_segments.Size() - _amount;
		while (m_segments.Size() != newSize) {
			m_segments.PopBack();
		}
	}
}

//check whether a snake has collided with itself
void Snake::CheckCollision() {
	if (m_direction != EDirection::e_none && !m_segments.IsEmpty()) {
		auto* currentNode = m_segments.GetHead();
		for (int i = 0; i < m_segments.Size(); ++i)
		{
			if (currentNode->m_position == m_position && !IsDead())
			{
				Collision(ECollisionType::e_self);
			}
			currentNode = currentNode->m_nextNode;
		}
	}
}

void Snake::Collision(const ECollisionType _collisionType) {
	if (!m_dead) {
		if (_collisionType == ECollisionType::e_wall || _collisionType == ECollisionType::e_snake || _collisionType == ECollisionType::e_self) {
			m_dead = true;
		}
	}
}

void Snake::Collision(Food* _food)
{
	if (_food->GetType() == eFoodType::e_gobble) {
		m_gobbleMode = true;
	}
	const int growAmount{ _food->GetGrowAmount() };
	Grow(growAmount);
}