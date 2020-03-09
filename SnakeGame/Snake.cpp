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

		if (m_direction != eRight)
		{
			m_direction = EDirection::eLeft;
		}
	}
	//right arrow
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (m_direction != eLeft) m_direction = EDirection::eRight;
	}
	//if the up arrow is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (m_direction != eDown) m_direction = EDirection::eUp;
	}
	//down arrow
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (m_direction != eUp) m_direction = EDirection::eDown;
	}
}


void Snake::Render(sf::RenderWindow& window) {
	for (auto itr = m_segments.begin(); itr != m_segments.end(); ++itr) {
		m_rectangle.setPosition(sf::Vector2f(itr->x, itr->y));
		window.draw(m_rectangle);
	}
}

Snake::Snake()
{
	m_colour = sf::Color::Red;
	int random{ 0 };

	while (m_position.x < 700 && m_position.x > 100) {
		//Generate a random x position 
		random = rand() % 44 + 1;
		m_position.x = random * 18;
	}

	while (m_position.y < 500 && m_position.y > 100) {
		//Generate a random y position 
		random = rand() % 33 + 1;
		m_position.y = random * 18;
	}

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
	case eLeft:
		m_position.x -= (k_Height + 5);
		break;
	case eRight:
		m_position.x += (k_Height + 5);
		break;
	case eUp:
		m_position.y -= (k_Height + 5);
		break;
	case eDown:
		m_position.y += (k_Height + 5);
		break;
	//default:
	//	break;
	}

	m_segments.pop_back();
	m_segments.push_front(sf::Vector2i(m_position.x, m_position.y));
}

void Snake::Grow(int amount)
{
	for (int i = 0; i < amount; ++i) {
		m_segments.push_back(sf::Vector2i(m_position.x, m_position.y));
	}
}
