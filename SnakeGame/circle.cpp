#include "circle.h"
#include "SFML/Graphics.hpp"
#include <iostream>

void Circle::Render(sf::RenderWindow& window)
{
	window.draw(circle);
}

Circle::Circle(sf::Color colourToBe, const sf::Vector2f vector, float radiusToBe, sf::Vector2f speedToBe) {
	colour = colourToBe;
	position = vector;
	radius = radiusToBe;
	speed = speedToBe;
	circle = sf::CircleShape(radiusToBe);
	circle.setFillColor(colourToBe);
	circle.setPosition(vector);
}

void Circle::Move(sf::RenderWindow& window) {
	//make it "bounce"
	if (position.x + speed.x <= 0 || position.x + speed.x >= window.getSize().x) {
		speed.x = -speed.x;
	}
	if (position.y + speed.y <= 0 || position.y + speed.y >= window.getSize().y) {
		speed.y = -speed.y;
	}
	circle.setPosition(position += speed);
}