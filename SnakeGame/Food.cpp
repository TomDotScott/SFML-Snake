#include "Food.h"
#include "SFML/Graphics.hpp"
#include <iostream>

void Food::Render(sf::RenderWindow& window)
{
	window.draw(m_circle);
}

Food::Food(sf::Color colour, const sf::Vector2f position, float radius, sf::Vector2f speed) 
	: Entity(colour, position, speed),
	m_radius(radius) 
{
	m_circle = sf::CircleShape(radius);
	m_circle.setFillColor(colour);
	m_circle.setPosition(position);
}

void Food::Move(sf::RenderWindow& window) {
	//make it "bounce"
	if (m_position.x + m_speed.x <= 0 || m_position.x + m_speed.x >= window.getSize().x) {
		m_speed.x = -m_speed.x;
	}
	if (m_position.y + m_speed.y <= 0 || m_position.y + m_speed.y >= window.getSize().y) {
		m_speed.y = -m_speed.y;
	}
	m_circle.setPosition(m_position += m_speed);
}