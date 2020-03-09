#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"

const int k_Radius = 8;

class Food : public Entity
{
private:
	float m_radius = k_Radius;
	sf::CircleShape m_circle;
public:
	Food();
	void Render(sf::RenderWindow& window);
	Food(sf::Color colour, sf::Vector2f position);
};