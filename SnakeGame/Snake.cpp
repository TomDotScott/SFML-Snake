#include "Snake.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <assert.h>

void Snake::Update(sf::RenderWindow& window) {
	Snake::Move();
	Snake::Render(window);
}

void::Snake::Input() {
	//if the left arrow is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		if (m_direction != EDirection::eRight)
		{
			m_direction = EDirection::eLeft;
		}
	}
	//right arrow
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (m_direction != EDirection::eLeft) m_direction = EDirection::eRight;
	}
	//if the up arrow is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (m_direction != EDirection::eDown) m_direction = EDirection::eUp;
	}
	//down arrow
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (m_direction != EDirection::eUp) m_direction = EDirection::eDown;
	}
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
	m_colour = sf::Color::Red;
	int random{ 0 };

	do {
		//Generate a random x position 
		random = rand() % 32 + 1;
		m_position.x = random * 25;
	} while (m_position.x <= 700 && m_position.x >= 100);


	do {
		//Generate a random y position 
		random = rand() % 24 + 1;
		m_position.y = random * 25;
	} while (m_position.y <= 500 && m_position.y >= 100);


	m_segments.push_back(sf::Vector2i(m_position.x, (m_position.y)));
	m_segments.push_back(sf::Vector2i(m_position.x - k_Height - 5, (m_position.y)));
	m_segments.push_back(sf::Vector2i(m_position.x - k_Height - 5, (m_position.y)));



	m_rectangle = sf::RectangleShape(sf::Vector2f((float)k_Height, (float)k_Height));
	m_rectangle.setFillColor(m_colour);
	m_rectangle.setPosition(m_position);
}

void Snake::Move() {
	//if the left arrow is pressed

	switch (m_direction)
	{
	case EDirection::eLeft:
		m_position.x -= (k_Height + 5);
		break;
	case EDirection::eRight:
		m_position.x += (k_Height + 5);
		break;
	case EDirection::eUp:
		m_position.y -= (k_Height + 5);
		break;
	case EDirection::eDown:
		m_position.y += (k_Height + 5);
		break;
	}

	CheckCollision();
	m_segments.pop_back();
	m_segments.push_front(sf::Vector2i(m_position.x, m_position.y));
}

void Snake::Grow(int amount)
{
	for (int i = 0; i < amount; ++i) {
		m_segments.push_back(sf::Vector2i(m_position.x, m_position.y));
	}
}

//check whether a snake has collided with itself
void Snake::CheckCollision() {
	if (m_direction != EDirection::eNone) {
		for (sf::Vector2i segment : m_segments) {
			if ((sf::Vector2f)segment == m_position && !m_isDead) {
				Collision("Self");
			}
		}
	}
}

void Snake::Collision(std::string collisionType) {
	if (collisionType == "Food") {
		Grow(3);
	}
	if (collisionType == "Self") {
		m_isDead = true;
	}
}
