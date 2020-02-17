#pragma once
#include "SFML/Graphics.hpp"
class Shape
{
protected:
	sf::Color colour;
	sf::Vector2f position;
	sf::Vector2f speed;
public:
	//setting the virtual function to 0 means it is a 'pure' virtual
	//this means that the function can only be called by its children
	//so therefore a Shape cannot exist on its own
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void Move(sf::RenderWindow& window) = 0;
};

