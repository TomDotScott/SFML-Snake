#pragma once
#include "SFML/Graphics.hpp"
#include "Shape.h"

class Rectangle : public Shape
{
private:
	float height = 1;
	float width = 2;
	sf::RectangleShape rectangle;
public:
	void Render(sf::RenderWindow& window);
	Rectangle(sf::Color colourToBe, sf::Vector2f vector, float heightToBe, float widthToBe, sf::Vector2f speedToBe);
	void Move(sf::RenderWindow& window);
};
