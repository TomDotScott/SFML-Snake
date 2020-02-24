#include "circle.h"
#include "SFML/Graphics.hpp"
#include <iostream>

void Circle::Render(sf::RenderWindow& window)
{
	window.draw(m_circle);
}

Circle::Circle(sf::Color colour, const sf::Vector2f position, float radius, sf::Vector2f speed) {
	m_colour = colour;
	m_position = position;
	m_radius = radius;
	m_speed = speed;
	m_circle = sf::CircleShape(radius);
	m_circle.setFillColor(colour);
	m_circle.setPosition(position);
}

void Circle::Move(sf::RenderWindow& window) {
	//make it "bounce"
	if (m_position.x + m_speed.x <= 0 || m_position.x + m_speed.x >= window.getSize().x) {
		m_speed.x = -m_speed.x;
	}
	if (m_position.y + m_speed.y <= 0 || m_position.y + m_speed.y >= window.getSize().y) {
		m_speed.y = -m_speed.y;
	}
	m_circle.setPosition(m_position += m_speed);
}