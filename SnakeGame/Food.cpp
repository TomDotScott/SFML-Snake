#include "Food.h"
#include "SFML/Graphics.hpp"
#include <iostream>

int Food::RandomRange(int min, int max) //range : [min, max)
{
	return min + rand() % ((max + 1) - min);
}

Food::Food()
{
	Randomise();
	m_circle = sf::CircleShape(static_cast<float>(Constants::k_snakeBlockSize) / 2);
}

Food::Food(sf::Color colour, sf::Vector2f position) : Entity(colour, position), m_type(eFoodType::e_standard)
{
	Randomise();
	m_circle = sf::CircleShape(static_cast<float>(Constants::k_snakeBlockSize) / 2);
}

void Food::Randomise() {
	//there will be 3 types of pickup. Standard, Special and Gobble Mode
	const int randomType = RandomRange(0, 100);
	//60% chance of being standard
	if (randomType <= 60) {
		m_type = eFoodType::e_standard;
	}
	//30% chance of being Special
	else if (randomType <= 90) {
		m_type = eFoodType::e_special;
	}
	//10% chance of being Gobble Mode
	else {
		m_type = eFoodType::e_gobble;
	}
	RandomisePosition();
}

void Food::RandomisePosition()
{
	//Find a random grid position
	//generate column number

	int randomNumber = RandomRange(4, static_cast<int>((Constants::k_screenWidth - 100) / Constants::k_snakeBlockSize));

	m_position.x = randomNumber * 25 >= Constants::k_screenWidth - 100
		               ? Constants::k_screenWidth - 100
		               : randomNumber * 25;

	randomNumber = RandomRange(4, static_cast<int>((Constants::k_screenHeight - 100) / Constants::k_snakeBlockSize));

	m_position.y = randomNumber * 25 >= Constants::k_screenHeight - 100
		               ? Constants::k_screenHeight - 100
		               : randomNumber * 25;

	std::cout << "FOOD LOCATION: " << m_position.x << " " << m_position.y << std::endl;

	m_circle.setPosition(m_position);
}

void Food::Render(sf::RenderWindow& window)
{
	switch (m_type) 
	{
	case eFoodType::e_standard:
		m_colour = sf::Color::Green;
		break;
	case eFoodType::e_special:
		m_colour = sf::Color::Magenta;
		break;
	case eFoodType::e_gobble:
		m_colour = sf::Color::Yellow;
		break;
	default:
		break;
	}
	m_circle.setPosition(m_position);
	m_circle.setFillColor(m_colour);
	window.draw(m_circle);
}

