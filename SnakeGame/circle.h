#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"

class Circle : public Entity
{
private:
	float m_radius = 1;
	sf::CircleShape m_circle;
public:
	void Render(sf::RenderWindow& window);
	void Move(sf::RenderWindow& window);
	Circle(sf::Color colourToBe, sf::Vector2f vector, float radius, sf::Vector2f speedToBe);
};

