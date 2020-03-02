#include "Snake.h"
#include "SFML/Graphics.hpp"
#include <iostream>

void Snake::Update(sf::RenderWindow& window) {
	Snake::Input();
	Snake::Move();
	Snake::Render(window);
}

void::Snake::Input() {
	//if the left arrow is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if(m_direction != eRight) m_direction = EDirection::eLeft;
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
	m_rectangle.setPosition(m_position);
	window.draw(m_rectangle);
}

Snake::Snake(sf::Color colour, const sf::Vector2f position, float height, float width, sf::Vector2f speed) {
	m_colour = colour;
	m_position = position;
	m_height = height;
	m_width = width;
	m_speed = speed;
	m_rectangle = sf::RectangleShape(sf::Vector2f(m_height, m_width));
	m_rectangle.setFillColor(colour);
	m_rectangle.setPosition(position);
}

void Snake::Move() {
	//if the left arrow is pressed
	switch (m_direction)
	{
	case eLeft:
		m_position.x -= m_speed.x;

		break;
	case eRight:
		m_position.x += m_speed.x;

		break;
	case eUp:
		m_position.y -= m_speed.y;

		break;
	case eDown:
		m_position.y += m_speed.y;

		break;
	default:
		break;
	}
}