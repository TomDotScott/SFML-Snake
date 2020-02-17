#include "Rectangle.h"
#include "SFML/Graphics.hpp"
#include <iostream>

void Rectangle::Render(sf::RenderWindow& window) {
	window.draw(rectangle);
}

Rectangle::Rectangle(sf::Color colourToBe, const sf::Vector2f vector, float heightToBe, float widthToBe, sf::Vector2f speedToBe) {
	colour = colourToBe;
	position = vector;
	height = heightToBe;
	width = widthToBe;
	speed = speedToBe;
	rectangle = sf::RectangleShape(sf::Vector2f(height, width));
	rectangle.setFillColor(colourToBe);
	rectangle.setPosition(vector);
}

void Rectangle::Move(sf::RenderWindow& window) {
	//make it "bounce"
	if (position.x + speed.x <= 0 || position.x + speed.x >= window.getSize().x) {
		speed.x = -speed.x;
	}
	if (position.y + speed.y <= 0 || position.y + speed.y >= window.getSize().y) {
		speed.y = -speed.y;
	}
	rectangle.setPosition(position += speed);
}