#include "Food.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Food::Food()
{
	//Generate a random x position 
	int random = rand() % 33 + 1;
	m_position.x = random * 25;

	//Generate a random y position 
	random = rand() % 24 + 1;
	m_position.y = random * 25;

	m_colour = sf::Color::Green;

	std::cout << "FOOD POSITION: " << m_position.x << " " << m_position.y << std::endl;
	m_circle = sf::CircleShape(k_Radius);
	m_circle.setFillColor(m_colour);
	m_circle.setPosition(m_position);
}

void Food::RandomisePosition()
{
	std::cout << "RANDOMISING POSITION" << std::endl;
	do {
		int random = rand() % 33 + 1;
		m_position.x = random * 25;
	} while (m_position.x <= 700 && m_position.x >= 100);

	do{
		//Generate a random y position 
		int random = rand() % 24 + 1;
		m_position.y = random * 25;
	} while (m_position.x <= 700 && m_position.x >= 100);

	std::cout << "NEW LOCATION: " << m_position.x << " " << m_position.y << std::endl;

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