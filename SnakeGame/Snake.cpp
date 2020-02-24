#include "Snake.h"
#include "SFML/Graphics.hpp"
#include <iostream>

void Snake::Render(sf::RenderWindow& window) {
	m_rectangle.setPosition(m_position);
	window.draw(m_rectangle);
}

Snake::Snake(sf::Color colour, const sf::Vector2f position, float height, float width, sf::Vector2f speed) {
	m_colour = colour;
	m_position = position;
	m_height = height;
	m_width = width;
	m_speed = speed;
	m_rectangle = sf::RectangleShape(sf::Vector2f(m_height, m_width));
	m_rectangle.setFillColor(colour);
	m_rectangle.setPosition(position);
}

void Snake::Move() {
	//if the left arrow is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_position.x -= m_speed.x;
	}
	//right arrow
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_position.x += m_speed.x;
	}
	//if the up arrow is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_position.y -= m_speed.y;
	}
	//down arrow
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_position.y += m_speed.y;
	}
	/*//make it "bounce"
	if (position.x + speed.x <= 0 || position.x + speed.x >= window.getSize().x) {
		speed.x = -speed.x;
	}
	if (position.y + speed.y <= 0 || position.y + speed.y >= window.getSize().y) {
		speed.y = -speed.y;
	}*/
	std::cout << m_position.x << " " << m_position.y << std::endl;

}