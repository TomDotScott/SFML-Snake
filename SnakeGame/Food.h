#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"

const float k_Radius = 9;

class Food : public Entity
{
private:
	float m_radius = k_Radius;
	sf::CircleShape m_circle;
public:
	Food();

	void RandomisePosition();

	void Render(sf::RenderWindow& window);

	Food(sf::Color colour, sf::Vector2f position);

	sf::Vector2f GetPosition() { return m_position; }
};