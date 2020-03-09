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