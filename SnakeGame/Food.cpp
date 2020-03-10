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
	m_circle = sf::CircleShape(Constants::kSnakeBlockSize / 2);
}

Food::Food(sf::Color colour, sf::Vector2f position) : Entity(colour, position)
{
	Randomise();
	m_circle = sf::CircleShape(Constants::kSnakeBlockSize / 2);
}

void Food::Randomise() {
	//there will be 3 types of pickup. +1, +3 and Gobble Mode
	int randomType = RandomRange(0, 3);
	if (randomType == 0) {
		m_type = eFoodType::eStandard;
	}
	else if (randomType == 1) {
		m_type = eFoodType::eSpecial;
	}
	else {
		m_type = eFoodType::eGobble;
	}
	RandomisePosition();
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
	switch (m_type) 
	{
	case eFoodType::eStandard:
		m_colour = sf::Color::Green;
		break;
	case eFoodType::eSpecial:
		m_colour = sf::Color::Magenta;
		break;
	case eFoodType::eGobble:
		m_colour = sf::Color::Yellow;
		break;
	default:
		break;
	}
	m_circle.setPosition(m_position);
	m_circle.setFillColor(m_colour);
	window.draw(m_circle);
}

