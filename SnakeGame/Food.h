#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Constants.h"

class Food : public Entity
{
private:
	sf::CircleShape m_circle;

	int random(int min, int max);

public:
	Food();

	void RandomisePosition();

	void Render(sf::RenderWindow& window);

	Food(sf::Color colour, sf::Vector2f position);

	sf::Vector2f GetPosition() { return m_position; }
};


