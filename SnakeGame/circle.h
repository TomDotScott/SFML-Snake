#pragma once
#include "SFML/Graphics.hpp"
#include "Shape.h"

class Circle : public Shape
{
private:
	float radius = 1;
	sf::CircleShape circle;
public:
	void Render(sf::RenderWindow& window);
	void Move(sf::RenderWindow& window);
	Circle(sf::Color colourToBe, sf::Vector2f vector, float radius, sf::Vector2f speedToBe);
};

