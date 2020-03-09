#include "Food.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Food::Food()
{
	//Generate a random x position 
	int random = rand() % 44 + 1;
	m_position.x = random * 18;

	//Generate a random y position 
	random = rand() % 33 + 1;
	m_position.y = random * 18;

	m_colour = sf::Color::Green;

	std::cout << "FINAL POSITION" << m_position.x << " " << m_position.y << std::endl;
	m_circle = sf::CircleShape(k_Radius);
	m_circle.setFillColor(m_colour);
	m_circle.setPosition(m_position);
}

void Food::Render(sf::RenderWindow& window)
{
	window.draw(m_circle);
}

Food::Food(sf::Color colour, sf::Vector2f position) : Entity(colour, position)
{
	m_circle = sf::CircleShape(k_Radius);
	m_circle.setFillColor(colour);
	m_circle.setPosition(position);
}