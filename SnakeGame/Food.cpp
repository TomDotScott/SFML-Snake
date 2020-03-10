#include "Food.h"
#include "SFML/Graphics.hpp"
#include <iostream>

int Food::RandomRange(int min, int max) //range : [min, max)
{
	return min + rand() % ((max + 1) - min);
}

Food::Food()
{
	RandomisePosition();

	m_colour = sf::Color::Green;

	//std::cout << "FOOD POSITION: " << m_position.x << " " << m_position.y << std::endl;
	m_circle = sf::CircleShape(Constants::kSnakeBlockSize / 2);
	m_circle.setFillColor(m_colour);
	m_circle.setPosition(m_position);
}

void Food::RandomisePosition()
{
	//Find a random grid position
	//generate column number

	int randomNumber = RandomRange(4, (int)(Constants::kScreenWidth - 100) / Constants::kSnakeBlockSize);
	if (randomNumber * 25 >= Constants::kScreenWidth - 100) {
		m_position.x = Constants::kScreenWidth - 100;
	}
	else {
		m_position.x = randomNumber * 25;
	}

	randomNumber = RandomRange(4, (int)(Constants::kScreenHeight - 100) / Constants::kSnakeBlockSize);
	if (randomNumber * 25 >= Constants::kScreenHeight - 100) {
		m_position.y = Constants::kScreenHeight - 100;
	}
	else {
		m_position.y = randomNumber * 25;
	}

	std::cout << "FOOD LOCATION: " << m_position.x << " " << m_position.y << std::endl;

	m_circle.setPosition(m_position);
}

void Food::Render(sf::RenderWindow& window)
{
	window.draw(m_circle);
}

Food::Food(sf::Color colour, sf::Vector2f position) : Entity(colour, position)
{
	m_position = sf::Vector2f(1, 1);
	RandomisePosition();

	m_colour = sf::Color::Green;

	//std::cout << "FOOD POSITION: " << m_position.x << " " << m_position.y << std::endl;
	m_circle = sf::CircleShape(Constants::kSnakeBlockSize / 2);
	m_circle.setFillColor(colour);
	m_circle.setPosition(position);
}